#ifndef UIVERTICALPOSITION_H
#define UIVERTICALPOSITION_H

#include "ui/uicommand.h"
#include "ui/encodecontrol.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>

/* вертикальное положение камеры*/
using EncodeControl::VerticalPositionEncodeFunction;


class UIVerticalPosition : public UICommand
{
    Q_OBJECT
public:
    explicit UIVerticalPosition( QWidget* parent = 0 );

    void setEFunction( const VerticalPositionEncodeFunction& value );
    void updateEncodeFunction( Payload_Type t );

private:
    QHBoxLayout* layout;
    QPushButton* btnVerticalPosition;

    VerticalPositionEncodeFunction eFunction;

private slots:
    void press();
};

#endif // UIVERTICALPOSITION_H
