#ifndef OPENFILEDIALOG_H
#define OPENFILEDIALOG_H

#include <QDialog>
#include <QTreeWidget>
#include <QFile>
#include <QFileInfo>
#include <QFileSystemModel>
#include <QStandardItemModel>
#include "resources/iconloader.h"
#include "resources/interface.h"

namespace Ui {
    class OpenFileDialog;
}

class OpenFileDialog : public QDialog
{
    Q_OBJECT

private:
    Ui::OpenFileDialog *ui;
    FILE_OPENER_MODE mode;
    QString workingPath;
    QString ext;
    QStringList * outFiles;

public:
    explicit OpenFileDialog(QString workPath, FILE_OPENER_MODE mode, QStringList * outFiles, QWidget *parent = 0);
    ~OpenFileDialog();
    static void GetStartFileList(QString workPath, FILE_OPENER_MODE mode, QStringList * outFiles);

private:
    void FillTree_PNG_OR_AVI(FILE_OPENER_MODE);
    void FillTree_PNG_OR_AVI(QTreeWidgetItem * parentItem = 0);
    void FillTree_PNG_AND_AVI(QString path, QTreeWidgetItem * parentItem);
    void FillTree_FOLDERS(QString path, QTreeWidgetItem * parentItem = 0);
    QFileInfoList GetSubItems(QFileInfo parent);
    QFileInfoList * GetUSBFlashDevices();

private slots:
    void open_Clicked();
    void cancel_Clicked();
};

#endif // OPENFILEDIALOG_H
