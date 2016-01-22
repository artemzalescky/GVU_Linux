#include "filesnavigator.h"
#include "ui_filesnavigator.h"

/*
  TO DO:
  import and export functions
  */

FilesNavigator::FilesNavigator(QString workingPath, bool canImport, bool canExport, bool canDelete, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FilesNavigator)
{
    this->workingPath = workingPath;
    ui->setupUi(this);
    this->canDelete = canDelete;
    this->canExport = canExport;
    this->canImport = canImport;

    vp = NULL;
    FillTree_PNG_AND_AVI();

    ui->delBtn->setEnabled(canDelete);
    ui->exportBtn->setEnabled(false);
    ui->importBtn->setEnabled(canImport);

    QObject::connect(ui->exportBtn, SIGNAL(clicked()), this, SLOT(exportBtn_Clicked()));
    QObject::connect(ui->importBtn, SIGNAL(clicked()), this, SLOT(importBtn_Clicked()));
    QObject::connect(ui->treeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(treeItemSelectionChanged()));
}

FilesNavigator::~FilesNavigator()
{
    if (vp != NULL)
    {
        delete vp;
        vp = NULL;
    }
    delete ui;
}

QFileInfoList FilesNavigator::GetSubItems(QFileInfo parent)
{
    QDir thisDir(parent.absoluteFilePath());
    return thisDir.entryInfoList();
}
void FilesNavigator::FillTree_PNG_OR_AVI(QTreeWidgetItem * parentItem)
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
void FilesNavigator::FillTree_PNG_AND_AVI()
{
    QString wpBU = workingPath;
    workingPath+="photo";
    QFileInfo dir(workingPath);
    if(dir.exists())
    {
        mode = FILE_OPENER_PHOTOS_ONLY;
        ext = "png";
        QTreeWidgetItem * topItem = new QTreeWidgetItem(ui->treeWidget);
        topItem->setText(0, QString::fromUtf8("Кадры"));
        topItem->setIcon(0,IconLoader::getIcon_FOLDERCLOSED());
        ui->treeWidget->addTopLevelItem(topItem);
        FillTree_PNG_OR_AVI(topItem);
    }
    workingPath = wpBU + "video";
    QFileInfo dir1(workingPath);
    if(dir1.exists())
    {
        mode = FILE_OPENER_VIDEO_ONLY;
        ext = "avi";
        QTreeWidgetItem * topItem = new QTreeWidgetItem(ui->treeWidget);
        topItem->setText(0, QString::fromUtf8("Видео"));
        topItem->setIcon(0,IconLoader::getIcon_FOLDERCLOSED());
        ui->treeWidget->addTopLevelItem(topItem);
        FillTree_PNG_OR_AVI(topItem);
    }
    mode = FILE_OPENER_PHOTOS_AND_VIDEO;
    workingPath = wpBU;
}

void FilesNavigator::PicturePreview(QString path)
{
    ui->lbl_v->setVisible(false);
    ui->lbl_p->setVisible(true);
    ui->lbl_p->setPixmap(QPixmap(path));
}

void FilesNavigator::VideoPreview(QString path)
{
    ui->lbl_p->setVisible(false);
    ui->lbl_v->setVisible(true);
    if(!vp)
    {
        vp = new VideoPlayerSmall(path,ui->previewWidget);
        vp->show();
    }
    vp->setSource(path);
}

QString FilesNavigator::GetSelectedFilePath(QTreeWidgetItem * item, bool isVideo)
{
    QString path = workingPath;
    if (isVideo)
        path += "video/";
    else
        path += "photo/";
    path += item->parent()->text(0);
    path += "/";
    path += item->text(0);
    return path;
}

void FilesNavigator::exportBtn_Clicked()
{
    QStringList * files = new QStringList();
    OpenFileDialog ofd(workingPath,FILE_OPENER_FOLDERS_ONLY, files, this);
    if (ofd.exec() == QDialog::Accepted)
    {
        return;
    }
}
void FilesNavigator::importBtn_Clicked()
{
    QStringList * files = new QStringList();
    OpenFileDialog ofd("/media",FILE_OPENER_PHOTOS_AND_VIDEO, files, this);
    if (ofd.exec() == QDialog::Accepted)
    {
        return;
    }
}

void FilesNavigator::treeItemSelectionChanged()
{
    if (ui->treeWidget->selectedItems()[0]->text(0).endsWith(".png", Qt::CaseInsensitive))
    {
        PicturePreview(GetSelectedFilePath(ui->treeWidget->selectedItems()[0], false));
        ui->exportBtn->setEnabled(canExport);
    }
    else if (ui->treeWidget->selectedItems()[0]->text(0).endsWith(".avi", Qt::CaseInsensitive))
    {
        ui->exportBtn->setEnabled(canExport);
        VideoPreview(GetSelectedFilePath(ui->treeWidget->selectedItems()[0],true));
    }
    else
        ui->exportBtn->setEnabled(false);
}
