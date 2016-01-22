#ifndef STREAMPLAYERSMALL_H
#define STREAMPLAYERSMALL_H

#include <QWidget>
#include <phonon/mediaobject.h>
#include <phonon/videowidget.h>
#include <phonon/videoplayer.h>
#include <phonon/path.h>
#include <phonon/backendcapabilities.h>
#include <QTime>
//#include <QtMultimedia>
//#include <QtMultimediaKit/QAudioInput>
//#include <QtMultimediaKit/QAudioOutput>

namespace Ui {
    class StreamPlayerSmall;
}

class StreamPlayerSmall : public QWidget
{
    Q_OBJECT

public:
    explicit StreamPlayerSmall(QWidget *parent = 0);
    ~StreamPlayerSmall();

private:
    Ui::StreamPlayerSmall *ui;
    QString url;
    Phonon::VideoPlayer *videoPlayer_;
};

#endif // STREAMPLAYERSMALL_H
