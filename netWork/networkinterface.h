#ifndef NETWORKINTERFACE_H
#define NETWORKINTERFACE_H

#include "resources/interface.h"
#include "data/datafromcamera.h"
#include <QUdpSocket>
#include "protocol.h"
#include <QObject>

#define PORT_TUNNEL_IN 42687
#define PORT_TUNNEL_OUT 42688

enum NetworkState {
    Connected = 0,
    NotConnected = 1
};


class NetworkInterface: public QObject
{
    Q_OBJECT

public:
    NetworkInterface();
    ~NetworkInterface();

private:
    QUdpSocket GVUSocket;    // сокет приема пакетов (с GCU)
    QUdpSocket GCUSocket;    // сокет отправки пакетов (на GCU)
    DataFromCamera* dataFromCamera;

    QHostAddress GCUAddress = QHostAddress( QString( "192.168.1.63" ) );

private slots:
    void ReadFromUDP();
    void ProcessData( QByteArray DataIn );
    void UDPStateChange( bool Enable );

public slots:
    void writeData( const QByteArray& data );
};

#endif // NETWORKINTERFACE_H
