#include "openfiledialog.h"
#include "ui_openfiledialog.h"

OpenFileDialog::OpenFileDialog(QString workPath, FILE_OPENER_MODE mode, QStringList * outFiles, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenFileDialog)
{
    this->outFiles = outFiles;
    workingPath = workPath;
    ui->setupUi(this);

    QFileInfoList * flashes;

    this->mode = mode;
    switch (mode)
    {
    case FILE_OPENER_PHOTOS_ONLY:
        ext = "png";
        workingPath += "photo";
        FillTree_PNG_OR_AVI();
        break;
    case FILE_OPENER_VIDEO_ONLY:
        ext = "avi";
        workingPath += "video";
        FillTree_PNG_OR_AVI();
        break;
    case FILE_OPENER_PHOTOS_AND_VIDEO:
        flashes = GetUSBFlashDevices();
        for(int i = 0; i < flashes->size(); i++)
        {
            QTreeWidgetItem * top = new QTreeWidgetItem(ui->treeWidget);
            top->setText(0, flashes->at(i).fileName());
            FillTree_PNG_AND_AVI(flashes->at(i).absoluteFilePath(), top);
        }
        break;
    case FILE_OPENER_FOLDERS_ONLY:
        flashes = GetUSBFlashDevices();
        for(int i = 0; i < flashes->size(); i++)
        {
            QTreeWidgetItem * top = new QTreeWidgetItem(ui->treeWidget);
            top->setText(0, flashes->at(i).fileName());
            FillTree_FOLDERS(flashes->at(i).absoluteFilePath(), top);
        }
        ui->treeWidget->setCurrentItem(ui->treeWidget->itemAt(0,0));
        break;
    }

    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(open_Clicked()));
    QObject::connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(cancel_Clicked()));
}

OpenFileDialog::~OpenFileDialog()
{
    delete ui;
}
QFileInfoList * OpenFileDialog::GetUSBFlashDevices()
{
    QFileInfoList * result = new QFileInfoList();

    QDir media("/media");
    if (!media.exists())
        return result;
    QFileInfoList dev = media.entryInfoList();
    for (int i = 0 ; i < dev.size(); i++)
    {
        if (dev.at(i).isFile() || dev.at(i).fileName() == "." || dev.at(i).fileName() == "..")
            continue;
        result->push_back(dev.at(i));
    }

    return result;
}

QFileInfoList OpenFileDialog::GetSubItems(QFileInfo parent)
{
    QDir thisDir(parent.absoluteFilePath());
    return thisDir.entryInfoList();
}
void OpenFileDialog::FillTree_PNG_OR_AVI(QTreeWidgetItem * parentItem)
{
    QFileInfo dir(workingPath);
    if(!dir.exists())
        return;

    QFileInfoList files = GetSubItems(dir);
    QTreeWidgetItem * topItem, * subItem;
    for (int i = 0; i < files.size(); i++)
    {
        if (files.at(i).fileName() == "." || files.at(i).fileName() == "..")
            continue;

        if (parentItem == 0)
            topItem = new QTreeWidgetItem(ui->treeWidget);
        else
            topItem = new QTreeWidgetItem(parentItem);

        topItem->setText(0, files.at(i).fileName());
        topItem->setIcon(0,IconLoader::getIcon_FOLDERCLOSED());

        QFileInfoList subfiles = GetSubItems(files.at(i));
        if (subfiles.size() == 0)
            continue;
        for (int k = 0; k < subfiles.size();k++)
        {
            if (subfiles.at(k).fileName() == "." || subfiles.at(k).fileName() == "..")
                continue;
            if (0 != subfiles.at(k).suffix().compare(ext,Qt::CaseInsensitive))
                continue;

            subItem = new QTreeWidgetItem(topItem);
            subItem->setText(0, subfiles.at(k).fileName());

            if (mode == FILE_OPENER_VIDEO_ONLY)
                subItem->setIcon(0,IconLoader::getIcon_FILEVIDEO());
            else if (mode == FILE_OPENER_PHOTOS_ONLY)
                subItem->setIcon(0,IconLoader::getIcon_FILEPHOTO());
        }
        ui->treeWidget->addTopLevelItem(topItem);
    }
    ui->treeWidget->setCurrentItem(ui->treeWidget->itemAt(0,0));
}


void OpenFileDialog::FillTree_PNG_OR_AVI(FILE_OPENER_MODE mode)
{
    ui->treeWidget->setColumnCount(1);
    QDir dir(workingPath);
    if(!dir.exists())
        return;
    QStringList entries = dir.entryList();
    int entN = entries.size();
    int subDirL;
    QTreeWidgetItem * topItem, * subItem;
    QDir * subDir;
    QStringList subEntries;
    for (int i = 0; i < entN; i++)
    {
        if (entries[i] == "." || entries[i] == "..")
            continue;

        topItem = new QTreeWidgetItem(ui->treeWidget);
        topItem->setText(0, entries[i]);
        topItem->setIcon(0,IconLoader::getIcon_FOLDERCLOSED());

        subDir = new QDir(workingPath + "/" + entries[i]);
        subEntries = subDir->entryList();
        subDirL = subEntries.size();
        for (int j = 0; j < subDirL; j++)
        {
            if (subEntries[j] == "." || subEntries[j] == "..")
                continue;
            if (!subEntries[j].endsWith(ext,Qt::CaseInsensitive))
                continue;

            subItem = new QTreeWidgetItem(topItem);
            subItem->setText(0, subEntries[j]);

            if (mode == FILE_OPENER_VIDEO_ONLY)
                subItem->setIcon(0,IconLoader::getIcon_FILEVIDEO());
            else
                subItem->setIcon(0,IconLoader::getIcon_FILEPHOTO());
        }

        ui->treeWidget->addTopLevelItem(topItem);
    }
    ui->treeWidget->setCurrentItem(ui->treeWidget->itemAt(0,0));
}

void OpenFileDialog::FillTree_PNG_AND_AVI(QString path, QTreeWidgetItem * parentItem)
{
    QFileInfo dir(path);
    if(!dir.exists())
        return;

    QFileInfoList dirs = GetSubItems(dir);
    QTreeWidgetItem * topItem;
    for (int i = 0; i < dirs.size(); i++)
    {
        if (dirs.at(i).fileName() == "." || dirs.at(i).fileName() == "..")
            continue;
        if (0 == dirs.at(i).suffix().compare("avi", Qt::CaseInsensitive))
        {
            if (parentItem == 0)
                topItem = new QTreeWidgetItem(ui->treeWidget);
            else
                topItem = new QTreeWidgetItem(parentItem);

            topItem->setText(0, dirs.at(i).fileName());
            topItem->setIcon(0,IconLoader::getIcon_FILEVIDEO());

            FillTree_PNG_AND_AVI(dirs.at(i).absoluteFilePath(), topItem);
            ui->treeWidget->addTopLevelItem(topItem);
        }
        else if (0 == dirs.at(i).suffix().compare("png", Qt::CaseInsensitive))
        {
            if (parentItem == 0)
                topItem = new QTreeWidgetItem(ui->treeWidget);
            else
                topItem = new QTreeWidgetItem(parentItem);

            topItem->setText(0, dirs.at(i).fileName());
            topItem->setIcon(0,IconLoader::getIcon_FILEPHOTO());

            FillTree_PNG_AND_AVI(dirs.at(i).absoluteFilePath(), topItem);
            ui->treeWidget->addTopLevelItem(topItem);
        }
        else if (dirs.at(i).isDir())
        {
            if (parentItem == 0)
                topItem = new QTreeWidgetItem(ui->treeWidget);
            else
                topItem = new QTreeWidgetItem(parentItem);

            topItem->setText(0, dirs.at(i).fileName());
            topItem->setIcon(0,IconLoader::getIcon_FOLDERCLOSED());

            FillTree_PNG_AND_AVI(dirs.at(i).absoluteFilePath(), topItem);
            ui->treeWidget->addTopLevelItem(topItem);
        }

    }
}

void OpenFileDialog::FillTree_FOLDERS(QString path, QTreeWidgetItem * parentItem)
{
    QFileInfo dir(path);
    if(!dir.exists())
        return;

    QFileInfoList dirs = GetSubItems(dir);
    QTreeWidgetItem * topItem;
    for (int i = 0; i < dirs.size(); i++)
    {
        if (dirs.at(i).fileName() == "." || dirs.at(i).fileName() == "..")
            continue;
        if (dirs.at(i).isFile())
            continue;

        if (parentItem == 0)
            topItem = new QTreeWidgetItem(ui->treeWidget);
        else
            topItem = new QTreeWidgetItem(parentItem);

        topItem->setText(0, dirs.at(i).fileName());
        topItem->setIcon(0,IconLoader::getIcon_FOLDERCLOSED());

        FillTree_FOLDERS(dirs.at(i).absoluteFilePath(), topItem);
        ui->treeWidget->addTopLevelItem(topItem);
    }
}

void OpenFileDialog::open_Clicked()
{
    QList<QTreeWidgetItem *> selItems = ui->treeWidget->selectedItems();
    if (selItems[0]->text(0).endsWith(ext, Qt::CaseInsensitive))
    {
        QString s = workingPath + "/" + selItems[0]->parent()->text(0) + "/" + selItems[0]->text(0);
        outFiles->push_back(s);
        outFiles->push_back(selItems[0]->text(0));
    }
    else
    {
        QDir * subDir = new QDir(workingPath + "/" + selItems[0]->text(0));
        QStringList subEntries = subDir->entryList();
        int subDirL = subEntries.size();
        for (int j = 0; j < subDirL; j++)
        {
             if (subEntries[j] == "." || subEntries[j] == "..")
                continue;
             if (!subEntries[j].endsWith(ext,Qt::CaseInsensitive))
                continue;
             outFiles->push_back(workingPath + "/" + selItems[0]->text(0) + "/" +  subEntries[j]);
             outFiles->push_back(subEntries[j]);
        }
    }
    accept();
}

void OpenFileDialog::cancel_Clicked()
{
    reject();
}


void OpenFileDialog::GetStartFileList(QString workPath, FILE_OPENER_MODE mode, QStringList * outFiles)
{
    QString workingPath = workPath;
    QString ext;

    switch (mode)
    {
    case FILE_OPENER_PHOTOS_ONLY:
        ext = ".png";
        workingPath += "photo";
        break;
    case FILE_OPENER_VIDEO_ONLY:
        ext = ".avi";
        workingPath += "video";
        break;
    case FILE_OPENER_PHOTOS_AND_VIDEO:
        outFiles = NULL;
        return;
    case FILE_OPENER_FOLDERS_ONLY:
        outFiles = NULL;
        return;
    }

    QDir dir(workingPath);
    if (dir.exists())
    {
        QStringList entries = dir.entryList();
        QDir * subDir = new QDir(workingPath + "/" + entries[entries.size()-1]);
        QStringList subEntries = subDir->entryList();
        int subDirL = subEntries.size();
        for (int j = 0; j < subDirL; j++)
        {
            if (subEntries[j] == "." || subEntries[j] == "..")
                continue;
            if (!subEntries[j].endsWith(ext,Qt::CaseInsensitive))
                continue;
            outFiles->push_back(workingPath + "/" + entries[entries.size()-1] + "/" + subEntries[j]);
            outFiles->push_back(subEntries[j]);
        }
    }
}
