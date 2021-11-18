#include "inc/networkcontroller/relayudpcontroller.h"


/*********************************************
 *                                           *
 *                PUBLIC METHODS             *
 *                                           *
 *********************************************/

RelayUdpController::RelayUdpController(QObject *parent)
    : QObject(parent),
      m_relayBoardUdpSocket(this),
      m_relayBoardUdpPort(0), // Init in slot_connectToRelayBoard
      m_relayBoardAddress(DEV_HOST)
{
    connect(&m_relayBoardUdpSocket, &QUdpSocket::readyRead,
            this, &RelayUdpController::slot_handleRelayUdpSocketReadyRead);
}

RelayUdpController::~RelayUdpController() {}

/*********************************************
 *                                           *
 *                PUBLIC SLOTS               *
 *                                           *
 *********************************************/

void RelayUdpController::slot_connectToRelayBoard(port_t udp_port)
{
    m_relayBoardUdpPort = udp_port;
    m_relayBoardUdpSocket.bind(QHostAddress::AnyIPv4,
                          udp_port);

#ifdef DEV_SANDBOX // Pingpong with the server
    qDebug() << "Bound on port:" << udp_port;
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=]() {
        qDebug() << "Sending Hello";
        this->sendMessage(QByteArray("Hello"));
    });
    timer->start(500);
#endif
}


/*********************************************
 *                                           *
 *                Private Methods            *
 *                                           *
 *********************************************/

void RelayUdpController::sendMessage(const QByteArray message) {
    QNetworkDatagram datagram(
                    message,
                    m_relayBoardAddress,
                    m_relayBoardUdpPort);
    m_relayBoardUdpSocket.writeDatagram(datagram);
}


/*********************************************
 *                                           *
 *                Private SLOTS              *
 *                                           *
 *********************************************/

void RelayUdpController::slot_handleRelayUdpSocketReadyRead()
{
    while (m_relayBoardUdpSocket.hasPendingDatagrams())
    {
        QNetworkDatagram datagram = m_relayBoardUdpSocket.receiveDatagram();
        QByteArray data = datagram.data();
        // Do interesting stuff with data
        qDebug() << "Received Data from RelayBoard UDP:" << data;
    }
}













