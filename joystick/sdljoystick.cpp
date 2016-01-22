#include "sdljoystick.h"
#include <QDebug>
#include <thread>

SDLJoystick::SDLJoystick( QObject* parent )
    : QObject( parent )
{
    //    qDebug() << this << "SDLJoystick";
    connect( &joystickTimer, SIGNAL( timeout() ), this, SLOT( onProcessEvent() ) );
    
    if ( SDL_Init( SDL_INIT_JOYSTICK ) != 0 ) {
//        qCritical() << "SDL_INIT_JOYSTICK is fail";
        return;
    }
    
    joystickTimer.start( JoyUpdateTime_ms );
    
    std::thread t( [this]() {
        SDL_Event event;
        
        while ( true ) {
            while ( SDL_WaitEvent( &event ) ) {
                if ( event.type == SDL_JOYDEVICEADDED || event.type == SDL_JOYDEVICEREMOVED ) {
                    onScan();
                }
            }
            
        }
    }
                 );
    t.detach();
}

SDLJoystick::~SDLJoystick()
{
    //qDebug() << this << "~SDLJoystick";
    if ( SDL_WasInit( SDL_INIT_JOYSTICK ) != 0 ) {
        SDL_Quit();
    }
}

int SDLJoystick::getCurrentJoyIndex() const
{
    return CurrentJoyIndex;
}

void SDLJoystick::setCurrentJoyIndex( int value )
{
    CurrentJoyIndex = value;
}

Joystick* SDLJoystick::getCurrentJoy() const
{
    if ( joys.isEmpty() ) {
        return nullptr;
    }
    else
        if ( CurrentJoyIndex < joys.size() ) {
            return joys.at( CurrentJoyIndex );
        }
        else {
            return nullptr;
        }
}

/* public slots */

void SDLJoystick::onScan()
{
    qDeleteAll( joys.begin(), joys.end() );
    joys.clear();
    int count = SDL_NumJoysticks();
    Joystick* j;
    
    for ( int i = 0; i < count; ++i ) {
        j = new Joystick();
        
        j->index = i;
        
        
        j->joy = SDL_JoystickOpen( i );
        
        j->name = SDL_JoystickName( j->joy );
        
        if ( !j->joy ) {
            return;
        }
        
        quint8 k;
        
        j->numAxes = SDL_JoystickNumAxes( j->joy );
        
        for ( k = 0; k < j->numAxes; ++k ) {
            j->axes[k] = 0;
        }
        
        j->numButtons = SDL_JoystickNumButtons( j->joy );
        
        for ( k = 0; k < j->numButtons; ++k ) {
            j->buttons[k] = 0;
        }
        
        j->numHats = SDL_JoystickNumHats( j->joy );
        
        for ( k = 0; k < j->numHats; ++k ) {
            j->hats[k] = 0;
        }
        
        joys.append( j );
        
//        qDebug( "idx: %d, name: %s (axes: %d, buttons: %d, hats: %d)",
//                j->index,
//				j->name,
//                j->numAxes,
//                j->numButtons,
//                j->numHats );
    }
    
    QListIterator<Joystick*> i( joys );
    emit joysChanged( count, i );
}

void SDLJoystick::onStart( int eventTimeout )
{
    joystickTimer.start( eventTimeout );
}

void SDLJoystick::onStop()
{
    joystickTimer.stop();
}

void SDLJoystick::onProcessEvent()
{

    Joystick* joy;
    int count = joys.size();
    
    for ( int j = 0; j < count; ++j ) {
//        qDebug() << j;

        Uint8 i;
        joy = joys.at( j );
        
        SDL_JoystickUpdate();
        
        for ( i = 0; i < joy->numAxes; ++i ) {
            if ( fabs( ( double )( joy->axes[i] - SDL_JoystickGetAxis( joy->joy, i ) ) / 65536 )  > joy->minAxisChange ) {
                qDebug() << "on_a_changed";
                joy->axes[i] = SDL_JoystickGetAxis( joy->joy, i );
                joy->on_a_changed( i, joy->axes[i] );
            }
        }
        
        for ( i = 0; i < joy->numButtons; ++i ) {
            if ( joy->buttons[i] != SDL_JoystickGetButton( joy->joy, i ) ) {
                qDebug() << "on_b_changed";
                joy->buttons[i] = SDL_JoystickGetButton( joy->joy, i );
                joy->on_b_changed( i, joy->buttons[i] );
            }
        }
        
        for ( i = 0; i < joy->numHats; ++i ) {
            if ( joy->hats[i] != SDL_JoystickGetHat( joy->joy, i ) ) {
                qDebug() << "on_h_changed";
                joy->hats[i] = SDL_JoystickGetHat( joy->joy, i );
                joy->on_h_changed( i, joy->hats[i] );
            }
        }
    }
    
    QListIterator<Joystick*> i( joys );
    emit dataChanged( count, i );
}
