#ifndef FACTORY_H
#define FACTORY_H

#include <QWidget>
#include <resources/interface.h>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>
#include <functional>
#include <QString>
#include <QDebug>

#include "resources/interface.h"
#include "ui/mode/uiMode.h"
#include "netWork/protocol.h"

namespace EncodeControl
{
    typedef std::function<QByteArray( int )> ZoomEncodeFunction;
    typedef std::function<QByteArray()> TakePhotoEncodeFunction;
    typedef std::function<QByteArray( int )> TakeSeriesPhotoEncodeFunction;
    typedef std::function<QByteArray()> RecordVideoEncodeFunction;
    typedef std::function <QByteArray( float, float )> RollAndPitchEncodeFunction;
    typedef std::function <QByteArray()> InitialPositionEncodeFunction;
    typedef std::function <QByteArray()> LandingPositionEncodeFunction;
    typedef std::function <QByteArray()> WorkingPositionEncodeFunction;
    typedef std::function <QByteArray()> VerticalPositionEncodeFunction;

    static const ZoomEncodeFunction MUSVPHOTO_ZOOM_ENCODE = []( int zoomLvl )->QByteArray {
        return protocolName::protocol::GenerateMessage( MUSV_SETTINGS,
        MUSV_SETTINGS_ZOOM,
        ( u_int8_t ) zoomLvl );
    };
    static const ZoomEncodeFunction MUSVTV_ZOOM_ENCODE = []( int zoomLvl )->QByteArray {
        return protocolName::protocol::GenerateMessage( MUSV_SETTINGS,
        MUSV_SETTINGS_ZOOM,
        ( u_int8_t ) zoomLvl );
    };
    static const ZoomEncodeFunction MUSVIR_ZOOM_ENCODE = []( int zoomLvl )->QByteArray {
        return protocolName::protocol::GenerateMessage( MUSV_SETTINGS,
        MUSV_SETTINGS_ZOOM,
        ( u_int8_t ) zoomLvl );
    };

    static const TakePhotoEncodeFunction FNTK_TAKE_PHOTO_ENCODE = []()->QByteArray {
        return protocolName::protocol::GenerateMessage( MUSV_SETTINGS,
        MUSV_SETTINGS_PHOTO,
        MUSV_SETTINGS_PHOTO_TAKE_PHOTO,
        0 );
    };
    static const TakePhotoEncodeFunction MUSVPHOTO_TAKE_PHOTO_ENCODE = []()->QByteArray {
        return protocolName::protocol::GenerateMessage( MUSV_SETTINGS,
        MUSV_SETTINGS_PHOTO,
        MUSV_SETTINGS_PHOTO_TAKE_PHOTO,
        0 );
    };

    static const TakeSeriesPhotoEncodeFunction FNTK_TAKE_SERIES_PHOTO_ENCODE = []( int nSec )->QByteArray {
        return  protocolName::protocol::GenerateMessage( MUSV_SETTINGS,
        MUSV_SETTINGS_PHOTO,
        MUSV_SETTINGS_PHOTO_BURST,
        ( u_int16_t ) ( nSec * 100 ) );
    };
    static const TakeSeriesPhotoEncodeFunction MUSVPHOTO_TAKE_SERIES_PHOTO_ENCODE = []( int nSec )->QByteArray {
        return protocolName::protocol::GenerateMessage( MUSV_SETTINGS,
        MUSV_SETTINGS_PHOTO,
        MUSV_SETTINGS_PHOTO_BURST,
        ( u_int16_t ) ( nSec * 100 ) );
    };

    static const RecordVideoEncodeFunction FNTK_RECORD_VIDEO_ENCODE = []()->QByteArray {
        return protocolName::protocol::GenerateMessage( MUSV_SETTINGS,
        MUSV_SETTINGS_PHOTO,
        MUSV_SETTINGS_RECORD,
        0 );
    };
    static const RecordVideoEncodeFunction MUSVPHOTO_RECORD_VIDEO_ENCODE = []()->QByteArray {
        return protocolName::protocol::GenerateMessage( MUSV_SETTINGS,
        MUSV_SETTINGS_PHOTO,
        MUSV_SETTINGS_RECORD,
        0 );
    };
    static const RecordVideoEncodeFunction MUSVTV_RECORD_VIDEO_ENCODE = []()->QByteArray {
        return protocolName::protocol::GenerateMessage( MUSV_SETTINGS,
        MUSV_SETTINGS_PHOTO,
        MUSV_SETTINGS_RECORD,
        0 );
    };

    static const RollAndPitchEncodeFunction MUSVPHOTO_ROLL_AND_PITCH_ENCODE = []( float roll, float pitch )->QByteArray {
        return  protocolName::protocol::GenerateAngles( ( float )  roll ,
        ( float )  pitch ,
        ( float ) 0.0  );
    };
    static const RollAndPitchEncodeFunction MUSVTV_ROLL_AND_PITCH_ENCODE = []( float roll, float pitch )->QByteArray {
        return  protocolName::protocol::GenerateAngles( ( float )  roll ,
        ( float )  pitch ,
        ( float ) 0.0  );
    };
    static const RollAndPitchEncodeFunction MUSVIR_ROLL_AND_PITCH_ENCODE = []( float roll, float pitch )->QByteArray {
        return  protocolName::protocol::GenerateAngles( ( float )  roll ,
        ( float )  pitch ,
        ( float ) 0.0  );
    };

    static const InitialPositionEncodeFunction MUSVPHOTO_INITIAL_POSITION_ENCODE = []()->QByteArray {
        qDebug() << "QByteArray не сформирован";
        QByteArray aByte;
        aByte.clear();

        return aByte;
    };
    static const InitialPositionEncodeFunction MUSVTV_INITIAL_POSITION_ENCODE = []()->QByteArray {
        qDebug() << "QByteArray не сформирован";
        QByteArray aByte;
        aByte.clear();

        return aByte;
    };
    static const InitialPositionEncodeFunction MUSVIR_INITIAL_POSITION_ENCODE = []()->QByteArray {
        qDebug() << "QByteArray не сформирован";
        QByteArray aByte;
        aByte.clear();

        return aByte;
    };

    static const LandingPositionEncodeFunction MUSVPHOTO_LANDING_POSITION_ENCODE = []()->QByteArray {
        qDebug() << "QByteArray не сформирован";
        QByteArray aByte;
        aByte.clear();

        return aByte;
    };
    static const LandingPositionEncodeFunction MUSVTV_LANDING_POSITION_ENCODE = []()->QByteArray {
        qDebug() << "QByteArray не сформирован";
        QByteArray aByte;
        aByte.clear();

        return aByte;
    };
    static const LandingPositionEncodeFunction MUSVIR_LANDING_POSITION_ENCODE = []()->QByteArray {
        qDebug() << "QByteArray не сформирован";
        QByteArray aByte;
        aByte.clear();

        return aByte;
    };

    static const VerticalPositionEncodeFunction MUSVTV_VERTICAL_POSITION_ENCODE = []()->QByteArray {
        qDebug() << "QByteArray не сформирован";
        QByteArray aByte;
        aByte.clear();

        return aByte;
    };
    static const VerticalPositionEncodeFunction MUSVIR_VERTICAL_POSITION_ENCODE = []()->QByteArray {
        qDebug() << "QByteArray не сформирован";
        QByteArray aByte;
        aByte.clear();

        return aByte;
    };

    static const WorkingPositionEncodeFunction MUSVPHOTO_WORKING_POSITION_ENCODE = []()->QByteArray {
        qDebug() << "QByteArray не сформирован";
        QByteArray aByte;
        aByte.clear();

        return aByte;
    };
    static const WorkingPositionEncodeFunction MUSVIR_WORKING_POSITION_ENCODE = []()->QByteArray {
        qDebug() << "QByteArray не сформирован";
        QByteArray aByte;
        aByte.clear();

        return aByte;
    };
    static const WorkingPositionEncodeFunction MUSVTV_WORKING_POSITION_ENCODE = []()->QByteArray {
        qDebug() << "QByteArray не сформирован";
        QByteArray aByte;
        aByte.clear();

        return aByte;
    };

    static ZoomEncodeFunction zoomEncode( Payload_Type pType );
    static TakePhotoEncodeFunction takePhotoEncode( Payload_Type pType );
    static TakeSeriesPhotoEncodeFunction takeSeriesPhotoEncode( Payload_Type pType );
    static RecordVideoEncodeFunction recordVideoEncode( Payload_Type pType );
    static RollAndPitchEncodeFunction rollAndPitchEncode( Payload_Type pType );
    static InitialPositionEncodeFunction initialPositionEncode( Payload_Type pType );
    static LandingPositionEncodeFunction landingPositionEncode( Payload_Type pType );
    static VerticalPositionEncodeFunction verticalPositionEncode( Payload_Type pType );
    static WorkingPositionEncodeFunction workingPositionEncode( Payload_Type pType);

}

#endif // FACTORY_H













/*
//-------------------------- M A P ------------------------------------------------------------

    static const map<Payload_Type, ZoomEncodeFunction> zoomEncodeMap = {
        std::pair<Payload_Type, ZoomEncodeFunction>( CAMERA_MUSVPHOTO, MUSVPHOTO_ZOOM_ENCODE ),
        std::pair<Payload_Type, ZoomEncodeFunction>( CAMERA_MUSVTV, MUSVTV_ZOOM_ENCODE ),
        std::pair<Payload_Type, ZoomEncodeFunction>( CAMERA_MUSVIR, MUSVIR_ZOOM_ENCODE )
    };
    static const map<Payload_Type, TakePhotoEncodeFunction> takePhotoEncodeMap = {
        std::pair<Payload_Type, TakePhotoEncodeFunction>( CAMERA_FNTK, FNTK_TAKE_PHOTO_ENCODE ),
        std::pair<Payload_Type, TakePhotoEncodeFunction>( CAMERA_MUSVPHOTO, MUSVPHOTO_TAKE_PHOTO_ENCODE ),
    };
    static const map<Payload_Type, TakeSeriesPhotoEncodeFunction> takeSeriesPhotoEncodeMap = {
        std::pair<Payload_Type, TakeSeriesPhotoEncodeFunction>( CAMERA_FNTK, FNTK_TAKE_SERIES_PHOTO_ENCODE ),
        std::pair<Payload_Type, TakeSeriesPhotoEncodeFunction>( CAMERA_MUSVPHOTO, MUSVPHOTO_TAKE_SERIES_PHOTO_ENCODE ),
    };
    static const map<Payload_Type, RecordVideoEncodeFunction> recordVideoEncodeMap = {
        std::pair<Payload_Type, RecordVideoEncodeFunction>( CAMERA_FNTK, FNTK_RECORD_VIDEO_ENCODE ),
        std::pair<Payload_Type, RecordVideoEncodeFunction>( CAMERA_MUSVPHOTO, MUSVPHOTO_RECORD_VIDEO_ENCODE ),
        std::pair<Payload_Type, RecordVideoEncodeFunction>( CAMERA_MUSVTV, MUSVTV_RECORD_VIDEO_ENCODE )
    };
    static const map<Payload_Type, RollAndPitchEncodeFunction> rollAndPitchEncodeMap = {
        std::pair<Payload_Type, RollAndPitchEncodeFunction>( CAMERA_MUSVPHOTO, MUSVPHOTO_ROLL_AND_PITCH_ENCODE ),
        std::pair<Payload_Type, RollAndPitchEncodeFunction>( CAMERA_MUSVTV, MUSVTV_ROLL_AND_PITCH_ENCODE ),
        std::pair<Payload_Type, RollAndPitchEncodeFunction>( CAMERA_MUSVIR, MUSVIR_ROLL_AND_PITCH_ENCODE )
    };
    static const map<Payload_Type, InitialPositionEncodeFunction> initialPositionEncodeMap = {
        std::pair<Payload_Type, InitialPositionEncodeFunction>( CAMERA_MUSVPHOTO, MUSVPHOTO_INITIAL_POSITION_ENCODE ),
        std::pair<Payload_Type, InitialPositionEncodeFunction>( CAMERA_MUSVTV, MUSVTV_INITIAL_POSITION_ENCODE ),
        std::pair<Payload_Type, InitialPositionEncodeFunction>( CAMERA_MUSVIR, MUSVIR_INITIAL_POSITION_ENCODE )
    };
    static const map < Payload_Type, LandingPositionEncodeFunction> landingPositionEncodeMap = {
        std::pair<Payload_Type, LandingPositionEncodeFunction>( CAMERA_MUSVPHOTO, MUSVPHOTO_LANDING_POSITION_ENCODE ),
        std::pair<Payload_Type, LandingPositionEncodeFunction>( CAMERA_MUSVTV, MUSVTV_LANDING_POSITION_ENCODE ),
        std::pair<Payload_Type, LandingPositionEncodeFunction>( CAMERA_MUSVIR, MUSVIR_LANDING_POSITION_ENCODE )
    };
    static const map<Payload_Type, VerticalPositionEncodeFunction> verticalPositionEncodeMap = {
        std::pair<Payload_Type, VerticalPositionEncodeFunction>( CAMERA_MUSVTV, MUSVTV_VERTICAL_POSITION_ENCODE ),
        std::pair<Payload_Type, VerticalPositionEncodeFunction>( CAMERA_MUSVIR, MUSVIR_VERTICAL_POSITION_ENCODE )
    };
    static const map <Payload_Type, WorkingPositionEncodeFunction> workingPositionEncodeMap = {
        std::pair<Payload_Type, WorkingPositionEncodeFunction>( CAMERA_MUSVTV, MUSVTV_WORKING_POSITION_ENCODE ),
        std::pair<Payload_Type, WorkingPositionEncodeFunction>( CAMERA_MUSVTV, MUSVTV_WORKING_POSITION_ENCODE ),
        std::pair<Payload_Type, WorkingPositionEncodeFunction>( CAMERA_MUSVIR, MUSVIR_WORKING_POSITION_ENCODE )
    };




// ---------------------------------------------------------------------------------------------



// ---------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------

*/
