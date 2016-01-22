#include "player_phonon.h"

PlayerPhonon::PlayerPhonon(QWidget* parent, QWidget* scroll) :
    QObject(parent)
{
    videoPlayer_ = new Phonon::VideoPlayer(Phonon::VideoCategory, parent);
    videoPlayer_->videoWidget()->setVisible(true);
    videoPlayer_->mediaObject()->setTickInterval(1000);
    videoPlayer_->setGeometry(QRect(0,0,720,576));

    videoPlayer_->show();

    seekSlider_ = new Phonon::SeekSlider(scroll);
    seekSlider_->setMediaObject(videoPlayer_->mediaObject());
    seekSlider_->setVisible(true);
    seekSlider_->setGeometry(QRect(0,0,720,20));

    ConnectSlots();
}

PlayerPhonon::~PlayerPhonon()
{
    if (videoPlayer_)
        videoPlayer_->close();
}

void PlayerPhonon::CreatePhononObjects(QWidget* parent, QWidget* scroll)
{
    videoPlayer_ = new Phonon::VideoPlayer(Phonon::VideoCategory, parent);
    videoPlayer_->videoWidget()->setVisible(true);
    videoPlayer_->mediaObject()->setTickInterval(1000);
    videoPlayer_->setGeometry(QRect(0,0,720,576));

    videoPlayer_->show();

    seekSlider_ = new Phonon::SeekSlider(scroll);
    seekSlider_->setMediaObject(videoPlayer_->mediaObject());
    seekSlider_->setVisible(true);
    seekSlider_->setGeometry(QRect(0,0,720,20));
}

void PlayerPhonon::ConnectSlots()
{
    QObject::connect(videoPlayer_->mediaObject(), SIGNAL(stateChanged(Phonon::State,Phonon::State)), this, SLOT(videoPlayer_stateChanged(Phonon::State,Phonon::State)));
    QObject::connect(videoPlayer_->mediaObject(), SIGNAL(tick(qint64)), this, SLOT(videoPlayer_tick(qint64)));
    QObject::connect(videoPlayer_->mediaObject(), SIGNAL(totalTimeChanged(qint64)), this, SLOT(videoPlayer_totalTimeChanged(qint64)));
    QObject::connect(videoPlayer_, SIGNAL(finished()), this, SLOT(videoPlayer_finished()));
}

bool PlayerPhonon::IsPaused()
{
    return videoPlayer_ ? videoPlayer_->isPaused() : false;
}
void PlayerPhonon::Play()
{
    if (videoPlayer_)
        videoPlayer_->play();
}

void PlayerPhonon::Play(QString src)
{
    Phonon::MediaSource psrc(src);
    if (!psrc.Invalid)
    {
        if (videoPlayer_)
            videoPlayer_->play(Phonon::MediaSource(psrc));
    }
}

void PlayerPhonon::Play(Phonon::MediaSource src)
{
    if (!src.Invalid)
    {
        if (videoPlayer_)
            videoPlayer_->play(src);
    }
}
void PlayerPhonon::Pause()
{
    if (videoPlayer_)
        videoPlayer_->pause();
}
void PlayerPhonon::Stop()
{
    if (videoPlayer_)
        videoPlayer_->stop();
}

void PlayerPhonon::videoPlayer_tick(qint64 time)
{
    emit Tick(time);
}

void PlayerPhonon::videoPlayer_stateChanged(Phonon::State newState_, Phonon::State oldState_)
{
    PlayerPhononState newState;
    switch (newState_)
    {
    case Phonon::ErrorState:
        newState = PlayerPhononState_ErrorState;
        break;
    case Phonon::PlayingState:
        newState = PlayerPhononState_PlayingState;
        break;
    case Phonon::StoppedState:
        newState = PlayerPhononState_StoppedState;
        break;
    case Phonon::PausedState:
        newState = PlayerPhononState_PausedState;
        break;
    case Phonon::BufferingState:
        newState = PlayerPhononState_BufferingState;
        break;
    default:
        break;
    }

    PlayerPhononState oldState;
    switch (oldState_)
    {
    case Phonon::ErrorState:
        oldState = PlayerPhononState_ErrorState;
        break;
    case Phonon::PlayingState:
        oldState = PlayerPhononState_PlayingState;
        break;
    case Phonon::StoppedState:
        oldState = PlayerPhononState_StoppedState;
        break;
    case Phonon::PausedState:
        oldState = PlayerPhononState_PausedState;
        break;
    case Phonon::BufferingState:
        oldState = PlayerPhononState_BufferingState;
        break;
    default:
        break;
    }

    emit StateChanged(newState,oldState);
}

void PlayerPhonon::videoPlayer_totalTimeChanged(qint64 time)
{
    emit TotalTimeChanged(time);
}

void PlayerPhonon::videoPlayer_finished()
{
    emit Finished();
}

void PlayerPhonon::changeHue(int h_)
{
    qreal h = (h_ - 50)/50.0;
    Phonon::VideoWidget * vW = videoPlayer_->videoWidget();
    vW->setHue(h);
}
void PlayerPhonon::changeSat(int br_)
{
    qreal br = (br_ - 50)/50.0;
    Phonon::VideoWidget * vW = videoPlayer_->videoWidget();
    vW->setSaturation(br);
}
void PlayerPhonon::changeBrightness(int br_)
{
    qreal br = (br_ - 50)/50.0;
    Phonon::VideoWidget * vW = videoPlayer_->videoWidget();
    vW->setBrightness(br);
}
void PlayerPhonon::changeContrast(int c_)
{
    qreal c = (c_ - 50)/50.0;
    Phonon::VideoWidget * vW = videoPlayer_->videoWidget();
    vW->setContrast(c);
}
