#ifndef DATAFROMCAMERA_H
#define DATAFROMCAMERA_H

#include <QObject>
#include"resources/interface.h"

class DataFromCamera: public QObject
{
    Q_OBJECT

public:
    DataFromCamera();

private:
    float roll;                 // крен
    float pitch;                // тангаж

    bool onState = false;       // состояние включения камеры(включена/выключена)
    iCamera_Mode mode;

public:
    float getRoll() const;
    void setRoll(float value);

    float getPitch() const;
    void setPitch(float value);

    bool getOnState() const;
    void setOnState(bool value);

    iCamera_Mode getMode() const;
    void setMode(const iCamera_Mode &value);

signals:
    void newRoll(float value);
    void newPitch(float value);

    void newOnState(bool value);            // новое состояние камеры
};


#endif // DATAFROMCAMERA_H
