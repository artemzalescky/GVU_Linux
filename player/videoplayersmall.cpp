#include "videoplayersmall.h"
#include "ui_videoplayersmall.h"

VideoPlayerSmall::VideoPlayerSmall(QString fileToPlay, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoPlayerSmall)
{
    ui->setupUi(this);
    src = fileToPlay;

    isplaying = false;
    ui->playBtn->setIcon(QIcon(IconLoader::getIcon_PLAY()));
    ui->playBtn->setToolTip(QString::fromUtf8("Показ"));

    videoPlayer_ = new Phonon::VideoPlayer(Phonon::VideoCategory, ui->widget);
    videoPlayer_->videoWidget()->setVisible(true);
    videoPlayer_->mediaObject()->setTickInterval(1000);
    videoPlayer_->setGeometry(QRect(0,0,ui->widget->width(),ui->widget->height()));
    videoPlayer_->show();

    seekSlider_ = new Phonon::SeekSlider(ui->widget_2);
    seekSlider_->setMediaObject(videoPlayer_->mediaObject());
    seekSlider_->setVisible(true);
    seekSlider_->setGeometry(QRect(0,0,ui->widget_2->width(),ui->widget_2->height()));

    QObject::connect(ui->playBtn, SIGNAL(clicked()), this, SLOT(playBtn_Clicked()));
}

VideoPlayerSmall::~VideoPlayerSmall()
{
    videoPlayer_->~VideoPlayer();
    delete ui;
}

void VideoPlayerSmall::setSource(QString src)
{
    if (isplaying)
    {
        playBtn_Clicked();
        videoPlayer_->stop();
    }
    this->src = src;
    playBtn_Clicked();
}

void VideoPlayerSmall::playBtn_Clicked()
{
    if (!isplaying)
    {
        if (videoPlayer_->isPaused())
            videoPlayer_->play();
        else
            videoPlayer_->play(Phonon::MediaSource(src));
        isplaying = true;
        ui->playBtn->setIcon(QIcon(IconLoader::getIcon_PAUSE()));
        ui->playBtn->setToolTip(QString::fromUtf8("Пауза"));
    }
    else
    {
        videoPlayer_->pause();
        isplaying = false;
        ui->playBtn->setIcon(QIcon(IconLoader::getIcon_PLAY()));
        ui->playBtn->setToolTip(QString::fromUtf8("Показ"));
    }
}
