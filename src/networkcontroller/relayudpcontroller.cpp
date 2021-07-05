#include "inc/networkcontroller/relayudpcontroller.h"

RelayUdpController::RelayUdpController(QObject *parent)
    : QObject(parent),
      m_relayUdpSocket(this)
{
}

RelayUdpController::~RelayUdpController() {}

void RelayUdpController::slot_connectToRelayBoard(port_t udp_port)
{
    QByteArray message("Message");
    QHostAddress relayBoard(DEV_HOST);
    QNetworkDatagram datagram(
                    message,
                    relayBoard,
                    udp_port);
    m_relayUdpSocket.writeDatagram(datagram);
}

