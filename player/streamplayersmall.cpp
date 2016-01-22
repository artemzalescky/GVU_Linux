#include "streamplayersmall.h"
#include "ui_streamplayersmall.h"

StreamPlayerSmall::StreamPlayerSmall(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StreamPlayerSmall)
{
    ui->setupUi(this);
    videoPlayer_ = new Phonon::VideoPlayer(Phonon::VideoCategory, this);
    videoPlayer_->videoWidget()->setVisible(true);
    videoPlayer_->mediaObject()->setTickInterval(1000);
    videoPlayer_->setGeometry(QRect(0,0,400,300));
    // url ="192.168.36.2";
    url ="v4l2://///dev/video0";
    videoPlayer_->play(Phonon::MediaSource(url));
}

StreamPlayerSmall::~StreamPlayerSmall()
{
    delete ui;
}
