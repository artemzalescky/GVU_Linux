#include "uiinitialposition.h"
#include <QDebug>


UIInitialPosition::UIInitialPosition( QWidget* parent ) : UICommand( parent )
{
    layout = new QHBoxLayout;

    btnInitialPosition = new QPushButton( "Начальное положение" );
    layout->addWidget( btnInitialPosition );

    setLayout( layout );

    connect( btnInitialPosition, SIGNAL( pressed() ), this, SLOT( press() ) );
}

void UIInitialPosition::setEFunction( const InitialPositionEncodeFunction& value )
{
    eFunction = value;
}

void UIInitialPosition::updateEncodeFunction( Payload_Type t )
{
    if ( t == CAMERA_MUSVPHOTO ) {
        setEFunction( EncodeControl::MUSVPHOTO_INITIAL_POSITION_ENCODE );
    }

    if ( t == CAMERA_MUSVTV ) {
        setEFunction( EncodeControl::MUSVTV_INITIAL_POSITION_ENCODE );
    }

    if ( t == CAMERA_MUSVIR ) {
        setEFunction( EncodeControl::MUSVIR_INITIAL_POSITION_ENCODE );
    }
}

void UIInitialPosition::press()
{
    qDebug() << "UIInitialPosition - Пакет данных не сформирован и не отправлен";

}

