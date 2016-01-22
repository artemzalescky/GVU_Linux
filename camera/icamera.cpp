#include "icamera.h"
#include "ui_icamera.h"
#include "QDebug"

ICamera::ICamera( QWidget* parent ) :
    QWidget( parent ),
    ui( new Ui::ICamera )
{
    ui->setupUi( this );
}

ICamera::~ICamera()
{
    delete ui;
}

///**
// * @brief ICamera::initCommands - инициализация команд управления камерой
// */
//void ICamera::initCommands( Payload_Type pType )
//{

//    Command* com;

//    for ( auto i : ControlPayloadMap.at( type ) ) {     //  i - список кнопок управления
//        if ( ( com = Factory::createCommand( i, pType ) ) != nullptr ) {
//            ModeCommandMap.insert( std::pair<iCamera_Mode, Command*>( com->getMode(), com ) );
//        }
//    }
//}
///**
// * @brief ICamera::initModes
// */
//void ICamera::initModes( Payload_Type type )
//{

//    changeModeCommand = Factory::createChangeModeCommand( ModePayloadMap[type], getDefaultMode( type ) );
//    connect( changeModeCommand, SIGNAL( newMode( iCamera_Mode ) ), this, SIGNAL( newCamMode( iCamera_Mode ) ) );
//}

iCamera_Mode ICamera::getDefaultMode( Payload_Type pType )
{

    if ( pType == CAMERA_FNTK ) {
        return fntk.mode;

    }

    if ( pType == CAMERA_MUSVPHOTO ) {
        return musvPhoto.mode;

    }

    if ( pType == CAMERA_MUSVTV ) {
        return musvTV.mode;
    }

    if ( pType == CAMERA_MUSVIR ) {
        return musvIR.mode;
    }
}
/**
 * @brief ICamera::getWidgets
 * @param mode
 * @return
 */
//std::vector<QWidget*> ICamera::getWidgetsControl( iCamera_Mode  mode )
//{
//    std::vector<QWidget*> widget;

//    for ( auto i = ModeCommandMap.cbegin(); i != ModeCommandMap.cend(); ++i ) {
//        if ( ( mode | i->first ) == i->first ) {
//            widget.push_back( i->second->getWidgetUI() );
//        }
//    }

//    return widget;
//}
/**
 * @brief ICamera::getWidgetChangeMode - получить виджет переключения режимов каммеры
 * @return
 */
//QWidget* ICamera::getWidgetChangeMode()
//{
//    QWidget* widget;
//    widget = changeModeCommand->getWidgetUI();

//    return widget;
//}
