#ifndef CAMERAANGLEVIEWER_H
#define CAMERAANGLEVIEWER_H

#include <QWidget>
#include <QGraphicsItem>
#include <qmath.h>

#include "resources/iconloader.h"

namespace Ui {
    class CameraAngleViewer;
}

/**
 * @brief The CameraAngleViewer class - направленность ЦН
 *
 * РАЗОБРАТЬСЯ С ПОЛУЧЕНИЕМ УГЛОВ С КАМЕРЫ !!!!!!!!!!!!!!
 *
 */
class CameraAngleViewer : public QWidget
{
    Q_OBJECT

public:
    explicit CameraAngleViewer(float y, float p, float z, QWidget *parent = 0);
    ~CameraAngleViewer();
    void redraw(float yaw, float pitch, float zoom);

private:
    Ui::CameraAngleViewer *ui;
    void paintEvent(QPaintEvent * /* event */);

    static const int drawerXPos = 3;
    static const int drawerYPos = 60;

    float yaw_, pitch_, zoom_;
public slots:
    void newRoll(float value);
    void newPitch(float value);
};

#endif // CAMERAANGLEVIEWER_H
