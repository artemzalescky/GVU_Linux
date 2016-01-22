#include "uirecordvideo.h"

UIRecordVideo::UIRecordVideo( QWidget* parent ) : UICommand( parent )
{
    layout = new QVBoxLayout;

    btnRecordVideo = new QPushButton( "Записать видео" );
    layout->addWidget( btnRecordVideo );

    setLayout( layout );

    connect( btnRecordVideo, SIGNAL( pressed() ), this, SLOT( press() ) );
}

void UIRecordVideo::setEFunction(const RecordVideoEncodeFunction &value)
{
    //?????????????????????????????????????????????????????
}
bool UIRecordVideo::getIsPressed() const
{
    return isPressed;
}

void UIRecordVideo::setIsPressed( bool value )
{
    isPressed = value;
}


void UIRecordVideo::press()
{
    if ( !isPressed ) {

        btnRecordVideo->setCheckable( true );
        isPressed = true;

//        sendCommandToPlane(protocolName::protocol::GenerateMessage( MUSV_SETTINGS,
//                                                                    MUSV_SETTINGS_PHOTO,
//                                                                    MUSV_SETTINGS_RECORD,
//                                                                    0 ));
    }
    else {
        btnRecordVideo->setCheckable( false );
        isPressed = false;

//        sendCommandToPlane(protocolName::protocol::GenerateMessage( MUSV_SETTINGS,
//                                                                    MUSV_SETTINGS_PHOTO,
//                                                                    MUSV_SETTINGS_RECORD,
//                                                                    0 ));
    }

}

void UIRecordVideo::updateEncodeFunction( Payload_Type t )
{
    if ( t == CAMERA_FNTK) {
        setEFunction( EncodeControl::FNTK_RECORD_VIDEO_ENCODE);
    }

    if ( t == CAMERA_MUSVPHOTO ) {
        setEFunction( EncodeControl::MUSVPHOTO_RECORD_VIDEO_ENCODE );
    }

    if ( t == CAMERA_MUSVTV ) {
        setEFunction( EncodeControl::MUSVTV_RECORD_VIDEO_ENCODE );
    }
}
bool UIRecordVideo::getVisibility() const
{
    return visibility;
}

void UIRecordVideo::setVisibility(bool value)
{
    visibility = value;
}

