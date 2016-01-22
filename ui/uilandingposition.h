#ifndef UILANDINGPOSITION_H
#define UILANDINGPOSITION_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <vector>

#include "ui/uicommand.h"
#include "ui/encodecontrol.h"

using EncodeControl::LandingPositionEncodeFunction;
/* посадочное положение камеры*/

class UILandingPosition : public UICommand
{
    Q_OBJECT

public:
    explicit UILandingPosition( QWidget* parent = 0 );
    bool getIsPressed() const;
    void setIsPressed(bool value);

    void setEFunction(const LandingPositionEncodeFunction &value);
    void updateEncodeFunction(Payload_Type t);

private:
    QHBoxLayout* layout;
    QPushButton* btnLandingPosition;

    bool isPressed = false;

    LandingPositionEncodeFunction eFunction;

private slots:
    void press();
};


#endif // UILANDINGPOSITION_H
