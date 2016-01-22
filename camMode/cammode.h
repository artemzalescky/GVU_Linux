#ifndef CAMMODE_H
#define CAMMODE_H

#include <QWidget>


namespace Ui {
    class CamMode;
}

class CamMode : public QWidget
{
    Q_OBJECT

public:
    explicit CamMode(QWidget *parent = 0);
    ~CamMode();
    void SetDescription(QWidget * desc);

private:
    Ui::CamMode *ui;
    QWidget * cameraDescription;

};

#endif // CAMMODE_H
