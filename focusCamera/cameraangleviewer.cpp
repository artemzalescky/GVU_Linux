#include "cameraangleviewer.h"
#include "ui_cameraangleviewer.h"
#include <QDebug>

CameraAngleViewer::CameraAngleViewer(float y, float p, float z, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraAngleViewer)
{
    yaw_ = y;
    pitch_ = p;
    zoom_ = z;
    ui->setupUi(this);
    ui->label->setPixmap(IconLoader::getIcon_PLANE());

    ui->drawer->update();
    redraw(0,0,1);
}
CameraAngleViewer::~CameraAngleViewer()
{
    delete ui;
}

void CameraAngleViewer::paintEvent(QPaintEvent * /* event */)
{
    ui->drawer->setVisible(false);
    QPainter painter(this);
    painter.setPen(QPen(QColor(10,10,10)));
    painter.setBrush(QBrush(QColor(255,255,255,120)));
    int cX, cY, size;
    size = qMax(25 * (1 + zoom_/10),(float)35);
    cX = ui->label->pos().x() + (ui->label->width())/2 + 30*qSin(yaw_);
    cY = ui->label->pos().y() + (ui->label->height())/2 + 30*qSin(pitch_);
    painter.drawRect(cX - size/2,cY - size/2,size,size);
}

void CameraAngleViewer::redraw(float yaw, float pitch, float zoom)
{
    yaw_ = yaw;
    pitch_ = pitch;
    zoom_ = zoom;

    ui->yaw->setText(QString("%1").arg(yaw_,0,'g',4));
    ui->pitch->setText(QString("%1").arg(pitch_,0,'g',4));
    ui->zoom->setText(QString("%1").arg(zoom_,0,'g',4));

    update();
    ui->label->raise();
}

void CameraAngleViewer::newRoll(float value)
{
    qDebug() << "show new Roll";
}

void CameraAngleViewer::newPitch(float value)
{
    qDebug() << "show new pitch";
}
