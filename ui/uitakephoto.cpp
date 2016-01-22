#include "uitakephoto.h"

UITakePhoto::UITakePhoto( QWidget* parent ) : UICommand( parent )
{
    layout = new QVBoxLayout;

    btnTakePhoto = new QPushButton( "сделать снимок" );
    layout->addWidget( btnTakePhoto );

    setLayout( layout );
    connect( btnTakePhoto, SIGNAL( pressed() ), this, SLOT( photo() ) );

}

void UITakePhoto::setEFunction(const TakePhotoEncodeFunction &value)
{
    eFunction = value;
}

void UITakePhoto::photo()
{

}

void UITakePhoto::updateEncodeFunction( Payload_Type t )
{
    if ( t == CAMERA_FNTK) {
        setEFunction( EncodeControl::FNTK_TAKE_PHOTO_ENCODE );
    }

    if ( t == CAMERA_MUSVPHOTO ) {
        setEFunction( EncodeControl::MUSVPHOTO_TAKE_PHOTO_ENCODE );
    }
}
bool UITakePhoto::getVisibility() const
{
    return visibility;
}

void UITakePhoto::setVisibility(bool value)
{
    visibility = value;
}


