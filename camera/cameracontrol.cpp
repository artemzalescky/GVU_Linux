#include "cameracontrol.h"
#include "ui_cameracontrol.h"
#include "QDebug"
#include "QLayout"

CameraControl::CameraControl( QWidget* parent ) :
    QWidget( parent ),
    ui( new Ui::ChooseCamera )
{
    ui->setupUi( this );

    createWidgets();


    // vector<QMyUIWidget*> UIs; // добавлние в вектор всех виджетов


    connect( ui->comboBox, SIGNAL( currentIndexChanged( int ) ), this, SLOT( changePayloadComboBox( int ) ) );
}

void CameraControl::changePayloadComboBox( int index )
{

    switch ( index ) {
        case 1: {
                if ( cam != nullptr ) {
                    delete cam;
                    cam = nullptr;
                }

                cam = createCam( CAMERA_FNTK );   // инициализация камеры
                emit chooseCamera( CAMERA_FNTK ); // сигнал о том, что подключена FNTK камера

                updateEncodeFunction( CAMERA_FNTK );


                // добавление режимов камеры

                // добавление функционала камеры

                break;
            }

        case 2: {
                if ( cam != nullptr ) {
                    delete cam;
                    cam = nullptr;
                }

                cam = createCam( CAMERA_MUSVPHOTO );    // инициализация камеры
                emit chooseCamera( CAMERA_MUSVPHOTO );  // сигнал о том, что подключена MUSVPHOTO

                updateEncodeFunction( CAMERA_MUSVPHOTO );

                break;
            }

        case 3: {
                if ( cam != nullptr ) {
                    delete cam;
                    cam = nullptr;
                }

                // MUSV TV
                cam = createCam( CAMERA_MUSVTV );   // инициализация камеры
                emit chooseCamera( CAMERA_MUSVTV ); // сигнал о том, что подключена MUSVTV

                updateEncodeFunction( CAMERA_MUSVTV );

                break;
            }

        case 4: {
                if ( cam != nullptr ) {
                    delete cam;
                    cam = nullptr;
                }

                // MUSV IR
                cam = createCam( CAMERA_MUSVIR );   // инициализация камеры
                emit chooseCamera( CAMERA_MUSVIR ); // сигнал о том, что подключена MUSVIR

                updateEncodeFunction( CAMERA_MUSVIR );

                break;
            }

        case 0: {

                break;
            }
    }
}

/**
 * @brief CameraControl::createCam - инициализация выбранной камеры
 * @param type - тип целевой нагрузки
 * @return
 */
ICamera* CameraControl::createCam( Payload_Type type )
{
    switch ( type ) {

        case CAMERA_FNTK: {
                cam = new FNTK();
                break;
            }

        case CAMERA_MUSVPHOTO: {
                cam = new MUSVPHOTO();
                break;
            }

        case CAMERA_MUSVTV: {
                cam = new MUSVTV();
                break;
            }

        case CAMERA_MUSVIR: {
                cam = new MUSVIR();
                break;
            }
    }

    return cam;
}

void CameraControl::createWidgets()
{
    zoom = new UIZoom();
    takePhoto = new UITakePhoto();
    takeSeriesPhoto = new UITakeSeriesPhoto();
    recordVideo = new UIRecordVideo();

    initialPosition = new UIInitialPosition();
    landingPosition = new UILandingPosition();
    verticalPosition = new UIVerticalPosition();
    workingPosition = new UIWorkingPosition();

    MyWidgetsUI.push_back( zoom );
    MyWidgetsUI.push_back( takePhoto );
    MyWidgetsUI.push_back( takeSeriesPhoto );
    MyWidgetsUI.push_back( recordVideo );

    MyWidgetsUI.push_back( initialPosition );
    MyWidgetsUI.push_back( landingPosition );
    MyWidgetsUI.push_back( verticalPosition );
    MyWidgetsUI.push_back( workingPosition );

}

void CameraControl::updateEncodeFunction( Payload_Type pType )
{

    qDebug() <<  " updateEncodeFunction " << pType;

    zoom->updateEncodeFunction( pType );
    takePhoto->updateEncodeFunction( pType );
    takeSeriesPhoto->updateEncodeFunction( pType );
    recordVideo->updateEncodeFunction( pType );

    initialPosition->updateEncodeFunction( pType );
    landingPosition->updateEncodeFunction( pType );
    verticalPosition->updateEncodeFunction( pType );
    workingPosition->updateEncodeFunction( pType );
}

CameraControl::~CameraControl()
{
    delete ui;
}







/*

vector<QMyUIWidget*> UIs;
for(wdg: UIs){
    wdg->updateEncodeFunction(newCamType);
}
cam->setMode(defaultoMode(newCamType));
for(wdg: UIs){
    wdg->updatevisibility(currentMode);
}

*/
























/*


/**
 * @brief CameraControl::addToForm - метод позволяет добавлять виджеты управления камерой на форму
 * @param wdg
 */
//void CameraControl::addToFormControlButton( std::vector<QWidget*> wdg )
//{
//    for ( auto & i : wdg ) {
//        ui->verticalLayout->addWidget( i );
//        i->show();
//    }
//}
/**
 * @brief CameraControl::addToFormModeRadioButton - метод позволяет добавить переключения  между режимами камеры на форму
 */
//void CameraControl::addToFormModeRadioButton( QWidget* wdg )
//{
//    ui->verticalLayoutMode->addWidget( wdg );
//    wdg->show();
//}

/**
 * @brief CameraControl::cleanWidget - метод позволяет удалять виджеты управления кмерой с формы
 */
/*
void CameraControl::cleanWidgetControl( )
{
    std::vector<QLayoutItem*> lItems;

    for ( int i = 0; i < ui->verticalLayout->layout()->count(); i++ ) {
        lItems.push_back( ui->verticalLayout->layout()->itemAt( i ) );
        lItems[i]->widget()->hide();
    }

    for ( auto i : lItems ) {
        ui->verticalLayout->layout()->removeItem( i );
    }
}

void CameraControl::cleanWidgetMode()
{
    std::vector<QLayoutItem*> lItems;

    for ( int i = 0; i < ui->verticalLayoutMode->layout()->count(); i++ ) {
        lItems.push_back( ui->verticalLayoutMode->layout()->itemAt( i ) );
        lItems[i]->widget()->hide();
    }

    for ( auto i : lItems ) {
        ui->verticalLayoutMode->layout()->removeItem( i );
    }
}
*/
