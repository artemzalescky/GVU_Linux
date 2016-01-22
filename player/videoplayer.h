#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QWidget>
#include <phonon/audiooutput.h>
#include <phonon/seekslider.h>
#include <phonon/mediaobject.h>
#include <phonon/volumeslider.h>
#include <phonon/videowidget.h>
#include <phonon/videoplayer.h>
#include <phonon/path.h>
#include <phonon/backendcapabilities.h>
#include <QList>
#include <QListWidgetItem>
#include <QTableWidgetItem>
#include <QTime>
#include <QMessageBox>
#include <QPainter>
#include <QDir>
//#include <QtMultimedia>
//#include <QtMultimediaKit/QAudioInput>
//#include <QtMultimediaKit/QAudioOutput>
#include "resources/iconloader.h"
#include "dialog/openfiledialog.h"

namespace Ui {
    class VideoPlayer;
}

class VideoPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit VideoPlayer(QString wordDir, QWidget *parent = 0);
    ~VideoPlayer();

private:
    void ConnectSlots();
    void CreatePhononObjects();
    void SetupPhononUI();

    void UpdateFiles();
    void UpdateButtonsState();
    void UpdatePlaying();

    void playNext();
    void ShowCurrentPlayingInTaskBar(const Phonon::MediaSource& source);
    void MarkPlayingItem(int index, bool bMark = true);
    void SetEnabledForToolButtons();

    void ShowCenter(bool);
    void ShowInfo(bool);

    void TogglePictureSettings(bool toggle);

    void Play();
    void Stop();
    void Next();
    void Prev();
    void Pause();
    void MakeSnap();

private:
    Ui::VideoPlayer *ui;

    Phonon::SeekSlider *seekSlider_;
    QList<Phonon::MediaSource> videoSources;
    Phonon::VideoPlayer *videoPlayer_;
    QTime displayTimeTotal_;
    int currentPlayIndex;

    bool isplaying;
    float sh, dolg;
    QString workingDirectory;
    QStringList filesToPlaySource;
    QStringList filesToPlayNames;
    QStringList * filesToPlay;

private slots:
    void playBtn_Clicked();
    void stopBtn_Clicked();
    void prevBtn_Clicked();
    void nextBtn_Clicked();
    void snapBtn_Clicked();
    void setBtn_Clicked(bool );
    void openBtn_Clicked();

    void tableWidget_itemDoubleClicked(QListWidgetItem* item);

    void videoPlayer_stateChanged(Phonon::State newState, Phonon::State oldState);
    void videoPlayer_tick(qint64 time);
    void videoPlayer_totalTimeChanged(qint64 time);
    void videoPlayer_finished();

    void changeBrightness(int);
    void changeContrast(int);
    void changeHue(int br_);
    void changeSat(int br_);
};

#endif // VIDEOPLAYER_H
