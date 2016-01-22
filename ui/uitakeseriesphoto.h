#ifndef UITAKESERIESPHOTO_H
#define UITAKESERIESPHOTO_H

#include "ui/uicommand.h"
#include "encodecontrol.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include "QLabel"
#include "QSpinBox"

using EncodeControl::TakeSeriesPhotoEncodeFunction;

class UITakeSeriesPhoto : public UICommand
{
    Q_OBJECT
public:
    explicit UITakeSeriesPhoto( QWidget* parent = 0 );

    bool getIsPressed() const;
    void setIsPressed( bool value );

    void setEFunction( const TakeSeriesPhotoEncodeFunction& value );
    void updateEncodeFunction( Payload_Type t );

    bool getVisibility() const;
    void setVisibility( bool value );

private:
    QHBoxLayout* layout;
    QSpinBox* spinBox;
    QPushButton* btnTakePhoto;
    QLabel* lbl;

    int nSec;
    bool isPressed = false;
    bool visibility = false;

    TakeSeriesPhotoEncodeFunction eFunction;


private slots:
    void press();
    void changeSpinBox( int value );
};

#endif // UITAKESERIESPHOTO_H
