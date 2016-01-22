#ifndef UIROLL_H
#define UIROLL_H

#include "ui/uicommand.h"
#include "encodecontrol.h"



#include <QWidget>
#include <QHBoxLayout>
#include <QSlider>
#include <QLabel>

//using EncodeControl::RollAndPitchEncodeFunction;


/* крен */
class UIRollAndPitch : public UICommand
{
    Q_OBJECT
public:
    explicit UIRollAndPitch( QWidget* parent = 0 );

    float calculateDegrees( int value );

    int getValueRoll() const;
    void setValueRoll( int value );

    int getValuePitch() const;
    void setValuePitch( int value );

//    void setEFunction( const RollAndPitchEncodeFunction& value );
    void updateEncodeFunction(Payload_Type t);

private:
    QVBoxLayout* mainLayout;
    QHBoxLayout* layoutRoll;
    QHBoxLayout* layoutPitch;

    QSlider* sliderRoll;
    QSlider* sliderPitch;

    QLabel* labelRoll;
    QLabel* labelPitch;
    QLabel* lblDegreesRoll;
    QLabel* lblDegreesPitch;

    int valueRoll;
    int valuePitch;

//    RollAndPitchEncodeFunction eFunction;

public slots:
    void newRoll( int value );
    void newPitch( int value );
};

#endif // UIROLL_H
