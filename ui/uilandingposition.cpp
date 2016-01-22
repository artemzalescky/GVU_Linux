#include "uilandingposition.h"


UILandingPosition::UILandingPosition( QWidget* parent ) : UICommand( parent )
{
    layout = new QHBoxLayout;

    btnLandingPosition = new QPushButton( "Посадочное положение" );
    layout->addWidget( btnLandingPosition );

    setLayout( layout );

    connect( btnLandingPosition, SIGNAL( pressed() ), this, SLOT( press() ) );
}

bool UILandingPosition::getIsPressed() const
{
    return isPressed;
}

void UILandingPosition::setIsPressed( bool value )
{
    isPressed = value;
}

void UILandingPosition::setEFunction( const LandingPositionEncodeFunction& value )
{
    eFunction = value;
}

void UILandingPosition::updateEncodeFunction( Payload_Type t )
{
    if ( t == CAMERA_MUSVPHOTO ) {
        setEFunction( EncodeControl::MUSVPHOTO_LANDING_POSITION_ENCODE );
    }

    if ( t == CAMERA_MUSVTV ) {
        setEFunction( EncodeControl::MUSVTV_LANDING_POSITION_ENCODE );
    }

    if ( t == CAMERA_MUSVIR ) {
        setEFunction( EncodeControl::MUSVIR_LANDING_POSITION_ENCODE );
    }
}

void UILandingPosition::press()
{
    // parking on
    // переводим камеру в посадочное положение, переходим в ТВ режим и задвигаем объектив

    qDebug() << "UILandingPosition - Пакет данных  не сформирован и не отправлен";


}
