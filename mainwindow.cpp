#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCodec>

MainWindow::MainWindow( QWidget* parent ) :
    QMainWindow( parent ),
    ui( new Ui::MainWindow )
{
    workingPath = QString::fromUtf8( "/home/gcu/QT-project/GVU_LINUX/" );
    QDir wDir( workingPath );

    if ( wDir.exists() ) {
        if ( !wDir.exists( "photo" ) ) {
            wDir.mkdir( QString( "photo" ) );
        }

        if ( !wDir.exists( "video" ) ) {
            wDir.mkdir( QString( "video" ) );
        }
    }

    ui->setupUi( this );
    ConnectSlots();

    ui->changeBtn->setIcon( IconLoader::getIcon_CHANGE() );
    ui->changeBtn->setToolTip( QString::fromUtf8( "сменить размер плейера" ) );

    smallInd = -1;
    mainInd = -1;
    QTextCodec* codec = QTextCodec::codecForName( "UTF-8" );
    QTextCodec::setCodecForCStrings( codec );

    dataFromCamera = new DataFromCamera();

    cameraAngleViewer = new CameraAngleViewer( 0, 0, 1, ui->tool1 );
    cameraAngleViewer->show();

    QObject::connect( dataFromCamera, SIGNAL( newRoll( float ) ), cameraAngleViewer, SLOT( newRoll( float ) ) );
    QObject::connect( dataFromCamera, SIGNAL( newPitch( float ) ), cameraAngleViewer, SLOT( newPitch( float ) ) );

    camera = new CameraControl( ui->tool3 );
    camera->show();

    QObject::connect( camera, SIGNAL( chooseCamera( Payload_Type ) ), this, SLOT( payload( Payload_Type ) ) );
    QObject::connect( camera, SIGNAL( chooseMode( iCamera_Mode ) ), this, SLOT( mode( iCamera_Mode ) ) );

    //-------- реализация джостика -------------------------------------------------------------------
//    joystick = new SDLJoystick();
//    joystick->onScan();

//    connect( joystick, SIGNAL( joysChanged( int, QListIterator<Joystick*> ) ),
//             this, SLOT( onJoysChange( int, QListIterator<Joystick*> ) ), Qt::DirectConnection );

//    connect( joystick, SIGNAL( dataChanged( int, QListIterator<Joystick*> ) ),
//             this, SLOT( onJoysDataChange( int, QListIterator<Joystick*> ) ), Qt::DirectConnection );

    //joyStickControl = new JoyStickControl();
    // -----------------------------------------------------------------------------------------------

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ConnectSlots()
{
    QObject::connect( ui->settingsBtn, SIGNAL( clicked() ), this, SLOT( settingsBtn_Clicked() ) );
    QObject::connect( ui->videoBtn, SIGNAL( clicked() ), this, SLOT( videoBtn_Clicked() ) );
    QObject::connect( ui->changeBtn, SIGNAL( clicked() ), this, SLOT( changeScreensBtn_Clicked() ) );
    QObject::connect( ui->reportBtn, SIGNAL( clicked() ), this, SLOT( reportBtn_Clicked() ) );
    QObject::connect( ui->filesBtn, SIGNAL( clicked() ), this, SLOT( fileBtn_Clicked() ) );

}

void MainWindow::udpateModePayload( Payload_Type pType )
{
    qDeleteAll( ui->tool2->children() );

    camMode = new CamMode( ui->tool2 );
    camMode->SetDescription( new CamModeDesc( payloadType, currentMode, camMode ) );
    camMode->show();
}

void MainWindow::videoBtn_Clicked()
{
    qDeleteAll( ui->mainFrame->children() );
    //videoPlayer = new VideoPlayer("/media/Data_/Video/Movies/Scrubs/", ui->mainFrame);
    videoPlayer = new VideoPlayer( workingPath, ui->mainFrame );
    videoPlayer->show();
    mainInd = 1;
}
void MainWindow::reportBtn_Clicked()
{
    qDeleteAll( ui->mainFrame->children() );
    reportPrepare = new ReportPrepare( workingPath, ui->mainFrame );
    reportPrepare->show();
    mainInd = 2;
}
void MainWindow::settingsBtn_Clicked()
{
    qDeleteAll( ui->mainFrame->children() );
    settingsModule = new AllSettngs( ui->mainFrame );
    settingsModule->show();
    mainInd = 5;
}
void MainWindow::fileBtn_Clicked()
{
    qDeleteAll( ui->mainFrame->children() );
    fileNav = new FilesNavigator( workingPath, true, true, false, ui->mainFrame );
    fileNav->show();
    mainInd = 6;
}

void MainWindow::changeScreensBtn_Clicked()
{
    if ( mainInd == 0 && smallInd == -1 ) {
        qDeleteAll( ui->mainFrame->children() );
        qDeleteAll( ui->smallFrame->children() );
        streamPlayerSmall = new StreamPlayerSmall( ui->smallFrame );
        streamPlayerSmall->show();
        mainInd = -1;
        smallInd = 0;
    }
    else
        if ( mainInd == -1 && smallInd == 0 ) {
            qDeleteAll( ui->mainFrame->children() );
            qDeleteAll( ui->smallFrame->children() );
            streamPlayer = new StreamPlayer( workingPath, photoMode, ui->mainFrame );
            streamPlayer->show();
            mainInd = 0;
            smallInd = -1;
        }
}

void MainWindow::payload( Payload_Type pType )
{
    payloadType = pType;
    qDeleteAll( ui->tool2->children() );

    camMode = new CamMode( ui->tool2 );
    camMode->SetDescription( new CamModeDesc( pType, currentMode, camMode ) );
    camMode->show();
}

void MainWindow::mode( iCamera_Mode cMode )
{
    currentMode = cMode;
    qDeleteAll( ui->mainFrame->children() );

    streamPlayer = new StreamPlayer( workingPath, cMode, ui->mainFrame );
    streamPlayer->show();
    mainInd = 0;

    udpateModePayload( payloadType );
}
