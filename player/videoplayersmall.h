#ifndef VIDEOPLAYERSMALL_H
#define VIDEOPLAYERSMALL_H

#include <QWidget>
#include <phonon/seekslider.h>
#include <phonon/mediaobject.h>
#include <phonon/videowidget.h>
#include <phonon/videoplayer.h>
#include <phonon/path.h>
#include <phonon/backendcapabilities.h>
#include "resources/iconloader.h"

namespace Ui {
    class VideoPlayerSmall;
}

class VideoPlayerSmall : public QWidget
{
    Q_OBJECT

public:
    explicit VideoPlayerSmall(QString fileToPlay, QWidget *parent = 0);
    ~VideoPlayerSmall();
    void setSource(QString src);

private:
    Ui::VideoPlayerSmall *ui;
    Phonon::SeekSlider *seekSlider_;
    Phonon::VideoPlayer *videoPlayer_;
    QString src;
    bool isplaying;



private slots:
    void playBtn_Clicked();
};

#endif // VIDEOPLAYERSMALL_H
