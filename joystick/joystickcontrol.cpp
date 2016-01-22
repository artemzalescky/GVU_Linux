#include "joystickcontrol.h"
#include <QDebug>

//static std::map<Joy_Key_Button, QAction*> joyMap = {
//    std::pair<Joy_Key_Button, QAction*>(StartView, pbStartView ),
//    std::pair<Joy_Key_Button, QAction*>(OnRecord, ),
//    std::pair<Joy_Key_Button, QAction*>(ParkingOn, ),
//    std::pair<Joy_Key_Button, QAction*>(ParkingOff, ),
//    std::pair<Joy_Key_Button, QAction*>(VerticalPosition, ),
//    std::pair<Joy_Key_Button, QAction*>(ColorModInc, ),
//    std::pair<Joy_Key_Button, QAction*>(ColorModDec, ),
//    std::pair<Joy_Key_Button, QAction*>(PreShoot, ),
//    std::pair<Joy_Key_Button, QAction*>(BurstMode, ),
//    std::pair<Joy_Key_Button, QAction*>(ZoomInc, ),
//    std::pair<Joy_Key_Button, QAction*>(ZoomDec, )
//};

//    if(joyMap.find(button) != joyMap.end()){
//        emit joyMap[bitton].triggered();
//    }

JoyStickControl::JoyStickControl()
{
    sdlJoystick = new SDLJoystick();
    currentJoystick = nullptr;
    sdlJoystick->onScan();


    connect( sdlJoystick, SIGNAL( joysChanged( int, QListIterator<Joystick*> ) ),
             this, SLOT( onJoysChange( int, QListIterator<Joystick*> ) ), Qt::DirectConnection );

}

void JoyStickControl::onJoysChange( int count, QListIterator<Joystick*> i )
{
    if ( count ) {
        Joystick* j;
        QString txt;

        while ( i.hasNext() ) {
            j = i.next();

            txt = QString( tr( "#%1 \"%2\" axes: %3, buttons: %4, hats: %5" ) )
                  .arg( j->index )
                  .arg( j->name )
                  .arg( j->numAxes )
                  .arg( j->numButtons )
                  .arg( j->numHats );
        }

        on_changeCurrentJoystick( j );

        txt = QString( tr( "founded %1 joysticks" ) ).arg( count );
    }
}

void JoyStickControl::on_changeCurrentJoystick( Joystick* newJoystick )
{
    currentJoystick = newJoystick;
    connect( currentJoystick, SIGNAL( a_changed( quint8, qint16 ) ), this, SLOT( on_a_changed( quint8 , qint16 ) ) );
    connect( currentJoystick, SIGNAL( b_changed( quint8, quint8 ) ), this, SLOT( on_b_changed( quint8, quint8 ) ) );
    connect( currentJoystick, SIGNAL( h_changed( quint8, quint8 ) ), this, SLOT( on_h_changed( quint8, quint8 ) ) );
}


void JoyStickControl::on_a_changed( quint8 axis, qint16 newValue )
{
    qDebug() << "on_a_changed" << axis << " : " << newValue;
}

void JoyStickControl::on_b_changed( quint8 button, quint8 newValue )
{
    qDebug() << "on_b_changed" << button << " : " << newValue;
    emit pushedButton( button );
}

void JoyStickControl::on_h_changed( quint8 hat, quint8 newValue )
{
    qDebug() << "on_h_changed" << hat << " : " << newValue;
}
