#ifndef UIZOOM_H
#define UIZOOM_H

#include "netWork/protocol.h"
#include "ui/uicommand.h"
#include "encodecontrol.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QLabel>
#include "functional"

#include "ui/encodecontrol.h"

using EncodeControl::ZoomEncodeFunction;

class UIZoom : public UICommand
{
    Q_OBJECT
public:
    explicit UIZoom( QWidget* parent = 0 );

    int getValueZoom() const;
    void setValueZoom( int value );

    bool checkZoom( int zoom );

    void setEFunction( const ZoomEncodeFunction& value );
    void updateEncodeFunction( Payload_Type t );

    bool getVisibility() const;
    void setVisibility(bool value);

private:
    QHBoxLayout* layout ;
    QSpinBox* spBoxZoomFNTK;
    QLabel* label;

    int valueZoom;
    const int MaxZoom = 12;
    bool visibility = false;    // по умолчанию - зум не виден

    ZoomEncodeFunction eFunction;

private slots:
    void zoom( int newZoom );

    void zoomInc( int newZoom );
    void zoomDes( int newZomm );

};

#endif // UIZOOM_H
