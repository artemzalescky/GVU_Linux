#ifndef UIINITIALPOSITION_H
#define UIINITIALPOSITION_H

#include "ui/uicommand.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>

#include <QWidget>
#include "functional"

#include "ui/encodecontrol.h"

using EncodeControl::InitialPositionEncodeFunction;

/* начальное положение камеры*/
class UIInitialPosition : public UICommand
{
    Q_OBJECT

public:
    explicit UIInitialPosition(QWidget *parent = 0);

    void setEFunction(const InitialPositionEncodeFunction &value);
    void updateEncodeFunction(Payload_Type t);

private:
    QHBoxLayout *layout;
    QPushButton * btnInitialPosition;

    InitialPositionEncodeFunction eFunction;

private slots:
   void press();
};

#endif // UIINITIALPOSITION_H
