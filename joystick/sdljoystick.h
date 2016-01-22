#ifndef SDLJOYSTICK_H
#define SDLJOYSTICK_H

#include <QObject>
#include <QTimer>
#include <QList>
#include <QListIterator>
#include "joystick.h"

constexpr int JoyUpdateTime_ms = 100;

class SDLJoystick : public QObject
{
    Q_OBJECT
    
    QTimer joystickTimer;
    int CurrentJoyIndex = 0;
    
public:
    QList<Joystick*> joys;
    
    explicit SDLJoystick( QObject* parent = 0 );
    ~SDLJoystick();
    
    
    Joystick* getCurrentJoy() const;
    
    int getCurrentJoyIndex() const;
    void setCurrentJoyIndex( int value );
    constexpr static int DefaultJoystickUpdateTime() {
        return JoyUpdateTime_ms;
    }

signals:
    void joysChanged( int count, QListIterator<Joystick*> i );
    void dataChanged( int count, QListIterator<Joystick*> i );
    
public slots:
    void onScan();
    void onStart( int eventTimeout = 20 );
    void onStop();
    void onProcessEvent();
};

#endif // SDLJOYSTICK_H
