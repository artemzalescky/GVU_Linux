#ifndef ICONLOADER_H
#define ICONLOADER_H

#include <QPixmap>

class IconLoader
{
public:    
    static QPixmap getIcon_PLAY()
    {
        return QPixmap("icons/play.ico");
    }

    static QPixmap getIcon_PAUSE()
    {
        return QPixmap("icons/pause.ico");
    }
    static QPixmap getIcon_STOP()
    {
        return QPixmap("icons/stop.ico");
    }
    static QPixmap getIcon_PREVIOUS()
    {
        return QPixmap("icons/prev.ico");
    }
    static QPixmap getIcon_NEXT()
    {
        return QPixmap("icons/next.ico");
    }
    static QPixmap getIcon_REC()
    {
        return QPixmap("icons/rec.ico");
    }
    static QPixmap getIcon_STOPREC()
    {
        return QPixmap("icons/stop.ico");
    }
    static QPixmap getIcon_COLORSETTINGS()
    {
        return QPixmap("icons/cset.ico");
    }
    static QPixmap getIcon_SNAP()
    {
        return QPixmap("icons/snap.ico");
    }
    static QPixmap getIcon_FILE()
    {
        return QPixmap("icons/file.ico");
    }
    static QPixmap getIcon_FILEVIDEO()
    {
        return QPixmap("icons/filevideo.ico");
    }
    static QPixmap getIcon_FILEPHOTO()
    {
        return QPixmap("icons/filephoto.ico");
    }
    static QPixmap getIcon_FOLDEROPENED()
    {
        return QPixmap("icons/folderopen.ico");
    }
    static QPixmap getIcon_FOLDERCLOSED()
    {
        return QPixmap("icons/folderclose.ico");
    }
    static QPixmap getIcon_OPEN()
    {
        return QPixmap("icons/open.ico");
    }
    static QPixmap getIcon_RECT()
    {
        return QPixmap("icons/rect.ico");
    }
    static QPixmap getIcon_ROUND()
    {
        return QPixmap("icons/round.ico");
    }
    static QPixmap getIcon_FREE()
    {
        return QPixmap("icons/free.ico");
    }
    static QPixmap getIcon_UNDO()
    {
        return QPixmap("icons/undo.ico");
    }
    static QPixmap getIcon_REDO()
    {
        return QPixmap("icons/redo.ico");
    }
    static QPixmap getIcon_ON()
    {
        return QPixmap("icons/on.ico");
    }
    static QPixmap getIcon_OFF()
    {
        return QPixmap("icons/off.ico");
    }
    static QPixmap getIcon_VIDEOCAM()
    {
        return QPixmap("icons/video.ico");
    }
    static QPixmap getIcon_PHOTOCAM()
    {
        return QPixmap("icons/photo.ico");
    }
    static QPixmap getIcon_IRCAM()
    {
        return QPixmap("icons/video.ico");
    }
    static QPixmap getIcon_ZOOM()
    {
        return QPixmap("icons/zoom.ico");
    }
    static QPixmap getIcon_UNZOOM()
    {
        return QPixmap("icons/unzoom.ico");
    }
    static QPixmap getIcon_PLANE()
    {
        return QPixmap("icons/plane.png");
    }
    static QPixmap getIcon_CHANGE(){
        return  QPixmap("icons/arrow.png");
    }


};


#endif // ICONLOADER_H
