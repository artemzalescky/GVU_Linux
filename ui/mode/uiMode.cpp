#include "uiMode.h"
#include <QDebug>


UIMode::UIMode( std::list<iCamera_Mode> listMode, iCamera_Mode defaultCamMode,  QWidget* parent )
{
    layout = new QVBoxLayout;

    for ( auto i : listMode ) {

        if ( i == photoMode ) {
            photoModeButton = new QRadioButton( "фоторежим" );
            layout->addWidget( photoModeButton );

            connect( photoModeButton, SIGNAL( pressed() ), this, SLOT( switchModePtoto() ) );
        }

        if ( i == videoMode ) {
            videoModeButton = new QRadioButton( "видеорежим" );
            layout->addWidget( videoModeButton );

            connect( videoModeButton, SIGNAL( pressed() ), this, SLOT( switchModeVideo() ) );
        }

        if ( i == irMode ) {
            irModeButton = new QRadioButton( "икрежим" );
            layout->addWidget( irModeButton );

            connect( irModeButton, SIGNAL( pressed() ), this, SLOT( switchModeIR() ) );
        }
    }

    setActiveRadioButton( defaultCamMode );
    setLayout( layout );
}

iCamera_Mode UIMode::getCurrentMode() const
{
    return currentMode;
}

void UIMode::setCurrentMode( const iCamera_Mode& value )
{
    currentMode = value;
}


void UIMode::setActiveRadioButton( iCamera_Mode camMode )
{
    if ( photoModeButton != nullptr && camMode == 1 ) {
        photoModeButton->setChecked( true );
    }

    if ( videoModeButton != nullptr && camMode == 2 ) {
        videoModeButton->setChecked( true );
    }

    if ( irModeButton != nullptr && camMode == 4 ) {
        irModeButton->setChecked( true );
    }

}

void UIMode::switchModePhoto()
{
    currentMode = photoMode;
    emit switchMode(photoMode);
}

void UIMode::switchModeVideo()
{
    currentMode = videoMode;
    emit switchMode(videoMode);
}

void UIMode::switchModeIR()
{
    currentMode = irMode;
    emit switchMode(videoMode);
}

