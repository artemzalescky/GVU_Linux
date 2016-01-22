#ifndef VIDEOWRITER_H
#define VIDEOWRITER_H

#include <QObject>
#include <QTimer>
#include <QWidget>
#include <QPixmap>
#include <QThread>

class Informer:public QThread
{
    Q_OBJECT

public:
    Informer();

    void run();
    void stop();

private:
    QTimer * timer;
    bool flag;

public slots:
    void onTimer();

signals:
    void newInfo(QString);
};

#endif // VIDEOWRITER_H
