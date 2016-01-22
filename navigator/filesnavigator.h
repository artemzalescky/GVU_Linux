#ifndef FILESNAVIGATOR_H
#define FILESNAVIGATOR_H

#include <QWidget>
#include "dialog/openfiledialog.h"
#include "resources/interface.h"
#include "resources/iconloader.h"
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include "player/videoplayersmall.h"

namespace Ui {
    class FilesNavigator;
}

class FilesNavigator : public QWidget
{
    Q_OBJECT

private:
    Ui::FilesNavigator *ui;
    QString workingPath, ext;
    bool canImport, canExport, canDelete;
    FILE_OPENER_MODE mode;
    VideoPlayerSmall * vp;

public:
    explicit FilesNavigator(QString workingPath, bool canImport, bool canExport, bool canDelete, QWidget *parent = 0);
    ~FilesNavigator();

private:
    void FillTree_PNG_OR_AVI(QTreeWidgetItem * parentItem = 0);
    void FillTree_PNG_AND_AVI();
    QFileInfoList GetSubItems(QFileInfo parent);

    void PicturePreview(QString path);
    void VideoPreview(QString path);
    QString GetSelectedFilePath(QTreeWidgetItem * item, bool isVideo);

private slots:
    void importBtn_Clicked();
    void exportBtn_Clicked();
    void treeItemSelectionChanged();
};

#endif // FILESNAVIGATOR_H
