#include "uizoom.h"


UIZoom::UIZoom( QWidget* parent ) : UICommand( parent )
{
    layout = new QHBoxLayout;
    spBoxZoomFNTK = new QSpinBox();
    label = new QLabel( "Zoom" );

    spBoxZoomFNTK->setMinimum( 0 ); // min zoom
    spBoxZoomFNTK->setMaximum( 12 ); // max zoom

    layout->addWidget( label );
    layout->addWidget( spBoxZoomFNTK );
    setLayout( layout );

    connect( spBoxZoomFNTK, SIGNAL( valueChanged( int ) ), this, SLOT( zoom( int ) ) );
}

int UIZoom::getValueZoom() const
{
    return valueZoom;
}

void UIZoom::setValueZoom( int value )
{
    valueZoom = value;
}

bool UIZoom::checkZoom( int zoom )
{
    return  ( ( zoom >= 1 ) && ( zoom <= 12 ) ) ? true : false;
}

void UIZoom::setEFunction( const ZoomEncodeFunction& value )
{
    eFunction = value;
}

void UIZoom::updateEncodeFunction( Payload_Type t )
{
    if ( t == CAMERA_MUSVPHOTO ) {
        setEFunction( EncodeControl::MUSVPHOTO_ZOOM_ENCODE );
    }

    if ( t == CAMERA_MUSVTV ) {
        setEFunction( EncodeControl::MUSVTV_ZOOM_ENCODE );
    }

    if ( t == CAMERA_MUSVIR ) {
        setEFunction( EncodeControl::MUSVIR_ZOOM_ENCODE );
    }
}
bool UIZoom::getVisibility() const
{
    return visibility;
}

void UIZoom::setVisibility(bool value)
{
    visibility = value;
}


void UIZoom::zoom( int newZoom )
{
    if ( newZoom > valueZoom ) {
        zoomInc( newZoom );
    }
    else {
        zoomDes( newZoom );
    }
}

void UIZoom::zoomInc( int newZoom )
{
    if ( !isVisible() ) {
        return;
    }

    if ( checkZoom( newZoom ) ) {

       // sendCommandToPlane( eFunction( ++valueZoom ) );
    }
}

void UIZoom::zoomDes( int newZoom )
{
    if ( !isVisible() ) {
        return;
    }

    if ( checkZoom( newZoom ) ) {

        sendCommandToPlane( eFunction( --valueZoom ) );
    }
}
