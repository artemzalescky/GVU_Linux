#include "networkinterface.h"

#define PORT_TUNNEL_IN 42687
#define PORT_TUNNEL_OUT 42688

NetworkInterface::NetworkInterface()
{
    GCUSocket.bind( QHostAddress::Any, PORT_TUNNEL_OUT );    // сокет принимает пакеты
    UDPStateChange( true );

    dataFromCamera = new DataFromCamera();

}

NetworkInterface::~NetworkInterface()
{
    UDPStateChange( false );
}

void NetworkInterface::UDPStateChange( bool Enable )
{
    if ( Enable ) {
        GVUSocket.bind( QHostAddress::Any, PORT_TUNNEL_IN );
        connect( &GVUSocket, SIGNAL( readyRead() ),
                 this, SLOT( ReadFromUDP() ) );
    }
    else {
        disconnect( &GVUSocket, SIGNAL( readyRead() ) );
        GVUSocket.close();
    }
}

void NetworkInterface::writeData( const QByteArray& data )
{
    GCUSocket.writeDatagram( data, QHostAddress::LocalHost, PORT_TUNNEL_OUT );
    GCUSocket.writeDatagram( data, GCUAddress, PORT_TUNNEL_OUT );
}

void NetworkInterface::ReadFromUDP()
{
    while ( GVUSocket.hasPendingDatagrams() ) {
        QByteArray datagram;
        datagram.resize( GVUSocket.pendingDatagramSize() );
        GVUSocket.readDatagram( datagram.data(), datagram.size() );
        ProcessData( datagram );
    }
}

void NetworkInterface::ProcessData( QByteArray DataIn )
{
    QByteArray Data = DataIn;
    QString str;

    for ( int i = 0; i < DataIn.size(); i++ ) {
        str += QString::number( ( u_int8_t ) DataIn[i], 16 );
    }
    qDebug() << "!!!!!!! " <<DataIn.size() << ":"<< str ;

    qDebug() << "Пришёл новый udp-пакет с gcu...необходимо его прочитать!!!";

    // инициализация roll, pitch.......
    dataFromCamera->setRoll( 10 );
    dataFromCamera->setPitch( 10 );

}
