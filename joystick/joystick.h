#ifndef JOYINFO_H
#define JOYINFO_H

#include <QObject>
#include <QMap>
#include <SDL2/SDL.h>

class Joystick : public QObject
{
    Q_OBJECT
public:
    Joystick();
    ~Joystick();

public:
    int index;
    QString name;
    int numAxes;
    int numButtons;
    int numHats;

    SDL_Joystick* joy;

    QMap<quint8, Sint16> axes;
    QMap<quint8, Uint8> buttons;
    QMap<quint8, Uint8> hats;
    
    double minAxisChange = 0.01; // минимальная чуствительность джойстика
    void on_b_changed( quint8 button, quint8  newValue ) {
        emit b_changed( button, newValue );
    }
    void on_a_changed( quint8 axis,   qint16 newValue ) {
        emit a_changed( axis,   newValue );
    }
    void on_h_changed( quint8 hat,    quint8  newValue ) {
        emit h_changed( hat,    newValue );
    }

signals:
    void b_changed( quint8 button, quint8  newValue );
    void a_changed( quint8 axis,   qint16 newValue );
    void h_changed( quint8 hat,    quint8  newValue );
};

#endif // JOYINFO_H
