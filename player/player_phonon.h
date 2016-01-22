#ifndef PLAYER_PHONON_H
#define PLAYER_PHONON_H

#include <QWidget>
#include <phonon/audiooutput.h>
#include <phonon/seekslider.h>
#include <phonon/mediaobject.h>
#include <phonon/volumeslider.h>
#include <phonon/videowidget.h>
#include <phonon/videoplayer.h>
#include <phonon/path.h>
#include <phonon/backendcapabilities.h>

enum PlayerPhononState
{
    PlayerPhononState_ErrorState,
    PlayerPhononState_PlayingState,
    PlayerPhononState_StoppedState,
    PlayerPhononState_PausedState,
    PlayerPhononState_BufferingState
};

// ЭТОТ КЛАСС НЕ ЗАВЕРШЕН И НЕ ИСПОЛЬЗУЕТСЯ В ТЕКУЩЕЙ ВЕРСИИ
class PlayerPhonon:public QObject
{
     Q_OBJECT

public:
    PlayerPhonon(QWidget* parent, QWidget* scroll);
    ~PlayerPhonon();

    void Play(Phonon::MediaSource);
    void Play(QString);
    void Play();
    void Stop();
    void Pause();
    bool IsPaused();

signals:
    void Tick(qint64);
    void StateChanged(PlayerPhononState,PlayerPhononState);
    void TotalTimeChanged(qint64);
    void Finished();

private:
    Phonon::SeekSlider *seekSlider_;
    Phonon::VideoPlayer *videoPlayer_;

    void CreatePhononObjects(QWidget* parent, QWidget* scroll);
    void ConnectSlots();

public slots:
    void changeBrightness(int);
    void changeContrast(int);
    void changeHue(int);
    void changeSat(int);

private slots:
    void videoPlayer_stateChanged(Phonon::State newState, Phonon::State oldState);
    void videoPlayer_tick(qint64 time);
    void videoPlayer_totalTimeChanged(qint64 time);
    void videoPlayer_finished();
};


#endif // PLAYER_PHONON_H
