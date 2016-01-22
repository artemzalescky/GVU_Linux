#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "settings/allsettngs.h"
#include "player/videoplayer.h"
#include "player/streamplayer.h"
#include "player/streamplayersmall.h"
#include "reportprepare.h"
#include "focusCamera/cameraangleviewer.h"
#include "camMode/cammode.h"
#include "camMode/cammodedesc.h"
#include "resources/interface.h"
#include "navigator/filesnavigator.h"
#include "data/datafromcamera.h"
#include "joystick/joystick.h"
#include "joystick/sdljoystick.h"

#include <QFrame>
#include <QMainWindow>
#include <QMouseEvent>
#include <QPoint>
#include <QTcpSocket>
#include <camera/fntk.h>
#include <camera/cameracontrol.h>
#include <resources/interface.h>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow( QWidget* parent = 0 );
    ~MainWindow();
    void SetStatusMessage( QString& msg );

private:
    void ConnectSlots();


private:
    Ui::MainWindow* ui;
    AllSettngs* settingsModule;
    VideoPlayer* videoPlayer;
    StreamPlayer* streamPlayer;
    StreamPlayerSmall* streamPlayerSmall;
    ReportPrepare* reportPrepare;
    CameraAngleViewer* cameraAngleViewer;
    CamMode* camMode;
    FilesNavigator* fileNav;
    QString workingPath;
    CameraControl* camera;
    DataFromCamera* dataFromCamera;
    //JoyStickControl *joyStickControl;

    iCamera_Mode currentMode;
    Payload_Type payloadType;



    int smallInd;
    int mainInd;

    void udpateModePayload( Payload_Type pType );

private slots:
    void videoBtn_Clicked();
    void settingsBtn_Clicked();
    void reportBtn_Clicked();
    void fileBtn_Clicked();

    void changeScreensBtn_Clicked();

   // void onJoysChange( int count, QListIterator<Joystick*> i );
   // void onJoysDataChange( int count, QListIterator<Joystick*> i );

    void payload( Payload_Type pType );
    void mode( iCamera_Mode cMode );

};

#endif // MAINWINDOW_H
