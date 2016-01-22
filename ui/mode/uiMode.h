#ifndef UIMODE_H
#define UIMODE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QRadioButton>
#include <list>
#include "resources/interface.h"


class UIMode : public QWidget
{
    Q_OBJECT
public:
    UIMode(std::list<iCamera_Mode> listMode ,iCamera_Mode defaultCamMode, QWidget* parent = 0 );

    iCamera_Mode getCurrentMode() const;
    void setCurrentMode(const iCamera_Mode &value);

private:
    QVBoxLayout* layout;
    QRadioButton* photoModeButton;
    QRadioButton* videoModeButton;
    QRadioButton* irModeButton;
    iCamera_Mode currentMode;

    void setActiveRadioButton(iCamera_Mode camMode);

signals:
    void switchMode(iCamera_Mode mode);

public slots:
    void switchModePhoto();
    void switchModeVideo();
    void switchModeIR();
};

#endif // UIPHOTOMODE_H
