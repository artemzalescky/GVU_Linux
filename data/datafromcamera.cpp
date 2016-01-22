#include "datafromcamera.h"

DataFromCamera::DataFromCamera()
{

}

float DataFromCamera::getRoll() const
{
    return roll;
}

void DataFromCamera::setRoll( float value )
{
    roll = value;

    emit newRoll( pitch );
}

float DataFromCamera::getPitch() const
{
    return pitch;
}

void DataFromCamera::setPitch( float value )
{
    pitch = value;

    emit newPitch( pitch );
}

bool DataFromCamera::getOnState() const
{
    return onState;
}

void DataFromCamera::setOnState( bool value )
{
    onState = value;
}

iCamera_Mode DataFromCamera::getMode() const
{
    return mode;
}

void DataFromCamera::setMode(const iCamera_Mode &value)
{
    mode = value;
}
