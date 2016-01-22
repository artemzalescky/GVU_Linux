#include "uiworkingposition.h"

UIWorkingPosition::UIWorkingPosition( QWidget* parent ) : UICommand( parent )
{
    layout = new QHBoxLayout;

    btnWorkingPosition = new QPushButton( "Вертикальное положение" );
    layout->addWidget( btnWorkingPosition );

    setLayout( layout );
    connect( btnWorkingPosition, SIGNAL( pressed() ), this, SLOT( press() ) );
}

void UIWorkingPosition::setEFunction(const EncodeControl::WorkingPositionEncodeFunction &value)
{
    eFunction = value;
}

void UIWorkingPosition::updateEncodeFunction(Payload_Type t)
{
    if ( t == CAMERA_MUSVPHOTO) {
        setEFunction( EncodeControl::MUSVPHOTO_WORKING_POSITION_ENCODE);
    }
    if ( t == CAMERA_MUSVTV) {
        setEFunction( EncodeControl::MUSVTV_WORKING_POSITION_ENCODE);
    }

    if ( t == CAMERA_MUSVIR ) {
        setEFunction( EncodeControl::MUSVIR_WORKING_POSITION_ENCODE );
    }
}

void UIWorkingPosition::press()
{
     qDebug() << "UIWorkingPosition - Пакет данных  не сформирован и не отправлен";
}

