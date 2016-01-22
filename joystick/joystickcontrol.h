#ifndef JOYSTICKCONTROL_H
#define JOYSTICKCONTROL_H

#include "joystick/joystick.h"
#include "joystick/sdljoystick.h"
#include "resources/interface.h"
#include <QAction>

#include <QObject>
#include <QMap>
#include <SDL2/SDL.h>

//QAction ZoomIncr;
//slot onZoomIncr{
//    if(Command zoom present in current mode)
//        CommandZomm->invoke(0,1);
//}

class JoyStickControl: public QObject
{
    Q_OBJECT

public:
    SDLJoystick* sdlJoystick;
    Joystick* currentJoystick;
private:
    static std::map<Joy_Key_Button, QAction> joyMap;
//    joyMapp[Joy_Key_Button]->trigger();
    QAction *pbStartView;
    QAction *pbOnRecord;
    QAction *pbParkingOn;
    QAction *pbParkingOff;
    QAction *pbVerticalPosition;
    QAction *pbColorModInc;
    QAction *pbColorModDec;
    QAction *pbPreShoot;
    QAction *pbBurstMode;
    QAction *pbShoot;
    QAction *pbZoomInc;
    QAction *pbZoomDec;
public:

    JoyStickControl();

public slots:
    void  on_changeCurrentJoystick( Joystick* newJoystick );
    void onJoysChange( int count, QListIterator<Joystick*> i );

    void on_a_changed( quint8 axis, qint16 newValue);
    void on_b_changed( quint8 button, quint8 newValue);
    void on_h_changed( quint8 hat, quint8 newValue);

signals:
    void pushedButton( quint8 number );
    void changeAxis();
    void changehat();

};

#endif // JOYSTICKCONTROL_H
