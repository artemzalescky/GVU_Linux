#ifndef UIWORKINGPOSITION_H
#define UIWORKINGPOSITION_H

#include "ui/uicommand.h"
#include "ui/encodecontrol.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>

/* рабочее положение камеры */
using EncodeControl::WorkingPositionEncodeFunction;

class UIWorkingPosition : public UICommand
{
    Q_OBJECT

public:
    explicit UIWorkingPosition(QWidget *parent = 0);

    void setEFunction( const WorkingPositionEncodeFunction& value );
    void updateEncodeFunction( Payload_Type t );

private:
    QHBoxLayout *layout;
    QPushButton * btnWorkingPosition;

    WorkingPositionEncodeFunction eFunction;

private slots:
    void press();

};

#endif // UIWORKINGPOSITION_H
