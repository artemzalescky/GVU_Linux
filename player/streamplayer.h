#ifndef STREAMPLAYER_H
#define STREAMPLAYER_H

#include <QWidget>
#include <phonon/mediaobject.h>
#include <phonon/videowidget.h>
#include <phonon/videoplayer.h>
#include <phonon/path.h>
#include <phonon/backendcapabilities.h>
#include <QTime>
#include <QDir>
#include <QPainter>
#include <QMessageBox>
//#include <QTcpSocket>
#include <QFile>
#include "resources/iconloader.h"
#include "resources/interface.h"
#include "settings/addcomswidgetvideo.h"
#include "player_qtgstreamer.h"
#include "informer/informer.h"
#include "resources/interface.h"


namespace Ui {
    class StreamPlayer;
}

class StreamPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit StreamPlayer(QString workDirectory, iCamera_Mode cameraType, QWidget *parent = 0);
    ~StreamPlayer();

private:
    Ui::StreamPlayer *ui;

    PlayerQtGstreamer * player;
    AddComsWidgetVideo * addCommandsWidget_video;

    bool isplaying;
    bool isrecording;
    int camYaw, camPitch, camZoom;
    float sh, dolg;
    iCamera_Mode camType;
    QString workingDirectory;

    Informer * di;


private:
    void ShowCenter();
    void ShowInfo();

    void TogglePictureSettings(bool toggle);
    void ToggleCameraManage(bool toggle);

    void ConnectSlots();

    bool Play();
    bool Pause();
    bool Record();
    bool StopRecord();
    void MakeSnap();

    void fmScan();
    void fmToStartPos();
    void fmLookAfter();
    void fmShot();
    void fmAutoShot();

private slots:
    void playBtn_Clicked();
    void recBtn_Clicked();
    void snapBtn_Clicked();
    void setBtn_Clicked(bool );


    void showAddCommands(bool);

    void changeBrightness(int);
    void changeContrast(int);
    void changeHue(int br_);
    void changeSat(int br_);

    void changeCamYaw(int );
    void changeCamPitch(int );
    void changeZoom(int );
};

#endif // STREAMPLAYER_H
