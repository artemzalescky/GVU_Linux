#include "uiverticalposition.h"

UIVerticalPosition::UIVerticalPosition( QWidget* parent ) : UICommand( parent )
{
    layout = new QHBoxLayout;

    btnVerticalPosition = new QPushButton( "Вертикальное положение" );
    layout->addWidget( btnVerticalPosition );

    setLayout( layout );

    connect( btnVerticalPosition, SIGNAL( pressed() ), this, SLOT( press() ) );
}

void UIVerticalPosition::setEFunction(const EncodeControl::VerticalPositionEncodeFunction &value)
{
    eFunction = value;
}


void UIVerticalPosition::updateEncodeFunction(Payload_Type t)
{

    if ( t == CAMERA_MUSVTV ) {
        setEFunction( EncodeControl::MUSVTV_VERTICAL_POSITION_ENCODE );
    }

    if ( t == CAMERA_MUSVIR ) {
        setEFunction( EncodeControl::MUSVIR_VERTICAL_POSITION_ENCODE );
    }
}

void UIVerticalPosition::press()
{
     qDebug() << "UIVerticalPosition - Пакет данных  не сформирован и не отправлен";
}

