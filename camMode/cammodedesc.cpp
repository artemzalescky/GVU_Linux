#include "cammodedesc.h"
#include "ui_cammodedesc.h"
#include <QDebug>

CamModeDesc::CamModeDesc( Payload_Type pType, iCamera_Mode mode, QWidget* parent ) :
    QWidget( parent ),
    ui( new Ui::PhotocamModeDesc )
{
    ui->setupUi( this );
    setType( pType );

    setOFF();
    setRegime( mode );
}

CamModeDesc::~CamModeDesc()
{
    delete ui;
}

void CamModeDesc::setON()
{
    ui->status->setPixmap( IconLoader::getIcon_ON() );
}

void CamModeDesc::setOFF()
{
    ui->status->setPixmap( IconLoader::getIcon_OFF() );
}

void CamModeDesc::setRegime( iCamera_Mode mode )
{
    switch ( mode ) {
        case photoMode: {
                ui->regime->setText( QString::fromUtf8( "фоторежим" ) );
                break;
            }

        case videoMode: {
                ui->regime->setText( QString::fromUtf8( "Видеорежим" ) );
                break;
            }

        case irMode:
            ui->regime->setText( QString::fromUtf8( "ИКрежим" ) );
            break;

        default: {
                ui->regime->setText( QString::fromUtf8( " - " ) );
                break;
            }
    }
}

void CamModeDesc::setType( Payload_Type type )
{
    switch ( type ) {
        case CAMERA_FNTK: {
                ui->type->setText( "ФНТК" );
                break;
            }

        case CAMERA_MUSVPHOTO: {
                ui->type->setText( "МУСВ ФОТО" );
                break;
            }

        case CAMERA_MUSVTV: {
                ui->type->setText( "МУСВ ТВ" );
                break;
            }

        case CAMERA_MUSVIR: {
                ui->type->setText( "МУСВ ИК" );
                break;
            }

        default: {
                ui->type->setText( " - " );
                break;
            }



    }
}
