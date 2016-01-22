#include "informer.h"


Informer::Informer()
{
    timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(onTimer()));
    run();
    flag = false;
}

void Informer::run()
{
    timer->start(500);
}

void Informer::stop()
{
    timer->stop();
}

void Informer::onTimer()
{
    QString s;
    if (flag)
        s = QString::fromUtf8("Ш:180 29' 32'' Д:180 29' 32'' В:1802    К:180.1 Т:180.1 Р:180.1");
    else
        s = QString::fromUtf8("Ш:181 29' 32'' Д:189 29' 32'' В:1800    К:126.1 Т:120.1 Р:160.0");

    flag = !flag;

    emit newInfo(s);
}
