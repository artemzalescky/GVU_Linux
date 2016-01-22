#include "uirollandpitch.h"

UIRollAndPitch::UIRollAndPitch( QWidget* parent ) : UICommand( parent )
{

    valueRoll = 0;
    valuePitch = 0;

    mainLayout = new QVBoxLayout;


    layoutRoll = new QHBoxLayout;
    layoutPitch = new QHBoxLayout;


    sliderRoll = new QSlider( Qt::Horizontal );
    labelRoll = new QLabel( "Крен" );
    lblDegreesRoll = new QLabel( "0" );

    sliderRoll->setMinimum( -32768 );
    sliderRoll->setMaximum( 32768 );
    sliderRoll->setValue( 0 );

    layoutRoll->addWidget( labelRoll );
    layoutRoll->addWidget( sliderRoll );
    layoutRoll->addWidget( lblDegreesRoll );


    sliderPitch = new QSlider( Qt::Horizontal );
    labelPitch = new QLabel( "Тангаж" );
    lblDegreesPitch = new QLabel( "0" );

    sliderPitch->setMinimum( -32768 );
    sliderPitch->setMaximum( 32768 );
    sliderPitch->setValue( 0 );

    layoutPitch->addWidget( labelPitch );
    layoutPitch->addWidget( sliderPitch );
    layoutPitch->addWidget( lblDegreesPitch );

    mainLayout->addLayout( layoutRoll );
    mainLayout->addLayout( layoutPitch );

    setLayout( mainLayout );

    connect( sliderRoll, SIGNAL( valueChanged( int ) ), this, SLOT( newRoll( int ) ) );
    connect( sliderPitch, SIGNAL( valueChanged( int ) ), this, SLOT( newPitch( int ) ) );
}

void UIRollAndPitch::newRoll( int value )
{
    valueRoll = value;
    lblDegreesRoll->setText( QString::number( calculateDegrees( sliderRoll->value() ) ) );

//    sendCommandToPlane( protocolName::protocol::GenerateAngles( ( float ) calculateDegrees( valueRoll ),
//                                                                ( float ) calculateDegrees( valuePitch ),
//                                                                ( float ) 0.0 ) );

}

void UIRollAndPitch::newPitch( int value )
{
    valuePitch = value;
    lblDegreesPitch->setText( QString::number( calculateDegrees( sliderPitch->value() ) ) );

//    sendCommandToPlane( protocolName::protocol::GenerateAngles( ( float ) calculateDegrees( valueRoll ),
//                                                                ( float ) calculateDegrees( valuePitch ),
//                                                                ( float ) 0.0 ) );
}

int UIRollAndPitch::getValueRoll() const
{
    return valueRoll;
}

void UIRollAndPitch::setValueRoll( int value )
{
    valueRoll = value;
}

int UIRollAndPitch::getValuePitch() const
{
    return valuePitch;
}

void UIRollAndPitch::setValuePitch( int value )
{
    valuePitch = value;
}

//void UIRollAndPitch::setEFunction(const RollAndPitchEncodeFunction &value)
//{
//    eFunction = value;
//}

void UIRollAndPitch::updateEncodeFunction(Payload_Type t)
{
    if ( t == CAMERA_MUSVPHOTO ) {
       // setEFunction( EncodeControl::MUSVPHOTO_ROLL_AND_PITCH_ENCODE );
    }
    if ( t == CAMERA_MUSVTV ) {
       // setEFunction( EncodeControl::MUSVTV_ROLL_AND_PITCH_ENCODE );
    }
    if ( t == CAMERA_MUSVIR ) {
       // setEFunction( EncodeControl::MUSVIR_ROLL_AND_PITCH_ENCODE );
    }
}

float UIRollAndPitch::calculateDegrees( int value )
{
    return ( float )( 90.0 * value ) / 32768.0;
}
