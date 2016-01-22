#include "uitakeseriesphoto.h"

UITakeSeriesPhoto::UITakeSeriesPhoto( QWidget* parent ) : UICommand( parent )
{
    layout = new QHBoxLayout;

    spinBox = new QSpinBox();
    spinBox->setMinimum( 0 );
    spinBox->setMaximum( 10 );
    spinBox->setValue( 1 );
    nSec = 1;

    btnTakePhoto = new QPushButton( "Кадр" );
    lbl = new QLabel( "кадр/сек" );

    layout->addWidget( spinBox );
    layout->addWidget( lbl );
    layout->addWidget( btnTakePhoto );

    setLayout( layout );

    connect( btnTakePhoto, SIGNAL( pressed() ), this, SLOT( press() ) );
    connect( spinBox, SIGNAL( valueChanged( int ) ), this, SLOT( changeSpinBox( int ) ) );

}

void UITakeSeriesPhoto::setEFunction( const TakeSeriesPhotoEncodeFunction& value )
{
    eFunction = value;
}

void UITakeSeriesPhoto::press()
{
    if ( !isPressed ) {
        btnTakePhoto->setCheckable( true );
        isPressed = true;
    }
    else {

        btnTakePhoto->setCheckable( false );
        isPressed = false;
    }
}

void UITakeSeriesPhoto::changeSpinBox( int value )
{
    nSec = value;
}

bool UITakeSeriesPhoto::getIsPressed() const
{
    return isPressed;
}

void UITakeSeriesPhoto::setIsPressed( bool value )
{
    isPressed = value;
}


void UITakeSeriesPhoto::updateEncodeFunction( Payload_Type t )
{
    if ( t == CAMERA_FNTK) {
        setEFunction( EncodeControl::FNTK_TAKE_SERIES_PHOTO_ENCODE);
    }

    if ( t == CAMERA_MUSVPHOTO ) {
        setEFunction( EncodeControl::MUSVPHOTO_TAKE_SERIES_PHOTO_ENCODE );
    }
}
bool UITakeSeriesPhoto::getVisibility() const
{
    return visibility;
}

void UITakeSeriesPhoto::setVisibility(bool value)
{
    visibility = value;
}

