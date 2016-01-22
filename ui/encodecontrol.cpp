#include "encodecontrol.h"
#include <QDebug>
#include <vector>
using std::vector;
using std::list;


EncodeControl::ZoomEncodeFunction EncodeControl::zoomEncode( Payload_Type pType )
{
    switch ( pType ) {
        case CAMERA_MUSVPHOTO: {
                return MUSVPHOTO_ZOOM_ENCODE;
            }

        case CAMERA_MUSVTV: {
                return MUSVTV_ZOOM_ENCODE;
            }

        case CAMERA_MUSVIR: {
                return MUSVIR_ZOOM_ENCODE;
            }
    }
}


EncodeControl::TakePhotoEncodeFunction EncodeControl::takePhotoEncode( Payload_Type pType )
{
    switch ( pType ) {
        case CAMERA_FNTK: {
                return FNTK_TAKE_PHOTO_ENCODE;
            }

        case CAMERA_MUSVPHOTO: {
                return MUSVPHOTO_TAKE_PHOTO_ENCODE;
            }

    }
}


EncodeControl::TakeSeriesPhotoEncodeFunction EncodeControl::takeSeriesPhotoEncode( Payload_Type pType )
{
    switch ( pType ) {
        case CAMERA_FNTK: {
                return FNTK_TAKE_SERIES_PHOTO_ENCODE;
            }

        case CAMERA_MUSVPHOTO: {
                return MUSVPHOTO_TAKE_SERIES_PHOTO_ENCODE;
            }

    }
}


EncodeControl::RecordVideoEncodeFunction EncodeControl::recordVideoEncode( Payload_Type pType )
{
    switch ( pType ) {
        case CAMERA_FNTK: {
                return FNTK_RECORD_VIDEO_ENCODE;
            }

        case CAMERA_MUSVPHOTO: {
                return MUSVPHOTO_RECORD_VIDEO_ENCODE;
            }

        case CAMERA_MUSVTV: {
                return MUSVTV_RECORD_VIDEO_ENCODE;
            }

    }
}


EncodeControl::RollAndPitchEncodeFunction EncodeControl::rollAndPitchEncode( Payload_Type pType )
{
    switch ( pType ) {

        case CAMERA_MUSVPHOTO: {
                return MUSVPHOTO_ROLL_AND_PITCH_ENCODE;
            }

        case CAMERA_MUSVTV: {
                return MUSVTV_ROLL_AND_PITCH_ENCODE;
            }

        case CAMERA_MUSVIR: {
                return MUSVIR_ROLL_AND_PITCH_ENCODE;
            }
    }
}


EncodeControl::InitialPositionEncodeFunction EncodeControl::initialPositionEncode( Payload_Type pType )
{
    switch ( pType ) {

        case CAMERA_MUSVPHOTO: {
                return MUSVPHOTO_INITIAL_POSITION_ENCODE;
            }

        case CAMERA_MUSVTV: {
                return MUSVTV_INITIAL_POSITION_ENCODE;
            }

        case CAMERA_MUSVIR: {
                return MUSVIR_INITIAL_POSITION_ENCODE;
            }
    }
}


EncodeControl::LandingPositionEncodeFunction EncodeControl::landingPositionEncode( Payload_Type pType )
{
    switch ( pType ) {

        case CAMERA_MUSVPHOTO: {
                return MUSVPHOTO_LANDING_POSITION_ENCODE;
            }

        case CAMERA_MUSVTV: {
                return MUSVTV_LANDING_POSITION_ENCODE;
            }

        case CAMERA_MUSVIR: {
                return MUSVIR_LANDING_POSITION_ENCODE;
            }
    }
}


EncodeControl::VerticalPositionEncodeFunction EncodeControl::verticalPositionEncode( Payload_Type pType )
{
    switch ( pType ) {

        case CAMERA_MUSVTV: {
                return MUSVTV_VERTICAL_POSITION_ENCODE;
            }

        case CAMERA_MUSVIR: {
                return MUSVIR_VERTICAL_POSITION_ENCODE;
            }
    }
}


EncodeControl::WorkingPositionEncodeFunction EncodeControl::workingPositionEncode( Payload_Type pType )
{
    switch ( pType ) {

        case CAMERA_MUSVPHOTO: {
                return MUSVTV_VERTICAL_POSITION_ENCODE;
            }

        case CAMERA_MUSVTV: {
                return MUSVTV_VERTICAL_POSITION_ENCODE;
            }

        case CAMERA_MUSVIR: {
                return MUSVIR_VERTICAL_POSITION_ENCODE;
            }
    }
}
