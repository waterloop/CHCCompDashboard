#include "inc/networkcontroller.h"
#include <QDebug>

NetworkController::NetworkController(QObject* parent)
    : QObject(parent),
      m_relayTcpSocket(this),
      m_relayUdpSocket(this)
{
    connect(&m_relayTcpSocket, &QAbstractSocket::errorOccurred,
            this, &NetworkController::slot_handleRelayTcpSocketErrorOccured);

    connect(&m_relayTcpSocket, &QAbstractSocket::connected,
            this, &NetworkController::slot_handleRelayTcpSocketConnected);

    connect(&m_relayTcpSocket, &QAbstractSocket::readyRead,
            this, &NetworkController::slot_handleRelayTcpSocketReadyRead);
}

NetworkController::~NetworkController()
{
    /**
      Cleanup relayTcpSocket
    */
    if (m_relayTcpSocket.isOpen()) {
        m_relayTcpSocket.close();
    }
}

void NetworkController::connectToRelayBoard()
{
#ifdef DEV_SANDBOX
    qDebug() << "Connecting to Relay board";
#endif
    m_relayTcpSocket.connectToHost(
                DEV_HOST,
                RELAY_BOARD_DEFAULT_TCP_PORT,
                QIODevice::ReadWrite,
                QAbstractSocket::IPv4Protocol);
}

// TODO: Add the error controller
void NetworkController::slot_handleRelayTcpSocketErrorOccured(
        QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::ConnectionRefusedError:
        qDebug() << "Unable to connect to Relay TCP, connection Refused";
        break;
    case QAbstractSocket::RemoteHostClosedError:
        /* Not really an Error, happens when ever the socket is closed by the
         other end */
        qDebug() << "Remote Host Closed Connection";
    default:
        qDebug() << "Unknown Error Recieved from relayboardTcpSocket" << socketError;
        break;
    }
}

void NetworkController::slot_handleRelayTcpSocketConnected()
{
    /* When Connected, Send the Handshake to initiate communication */
    QByteArray handshake(RELAY_BOARD_HANDSHAKE_REQUEST);
    m_relayTcpSocket.write(handshake);
}

void NetworkController::slot_handleRelayTcpSocketReadyRead()
{
    QByteArray response = m_relayTcpSocket.readAll();
    qDebug() << "Response Received" << response;
    // TODO: Parse result and handle acordingly
}
