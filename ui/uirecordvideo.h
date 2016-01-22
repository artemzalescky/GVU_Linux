#ifndef UIRECORDVIDEO_H
#define UIRECORDVIDEO_H

#include "ui/uicommand.h"
#include "encodecontrol.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <vector>


using EncodeControl::RecordVideoEncodeFunction;

class UIRecordVideo : public UICommand
{
    Q_OBJECT

public:
    explicit UIRecordVideo(QWidget *parent = 0);

    bool getIsPressed() const;
    void setIsPressed(bool value);

    void setEFunction(const RecordVideoEncodeFunction &value);    
    void updateEncodeFunction(Payload_Type t);

    bool getVisibility() const;
    void setVisibility(bool value);

private:
    RecordVideoEncodeFunction eFunction;

private:
    QVBoxLayout* layout;
    QPushButton* btnRecordVideo;

    bool isPressed = false;
    bool visibility = false;

private slots:
    void press();
};

#endif // UIRECORDVIDEO_H
