#include "inc/networkcontroller.h"
#include <QDebug>

RelayTcpController::RelayTcpController(QObject* parent)
    : QObject(parent),
      m_relayTcpSocket(this)
{
    connect(&m_relayTcpSocket, &QAbstractSocket::errorOccurred,
            this, &RelayTcpController::slot_handleRelayTcpSocketErrorOccured);

    connect(&m_relayTcpSocket, &QAbstractSocket::connected,
            this, &RelayTcpController::slot_handleRelayTcpSocketConnected);

    connect(&m_relayTcpSocket, &QAbstractSocket::readyRead,
            this, &RelayTcpController::slot_handleRelayTcpSocketReadyRead);
}

RelayTcpController::~RelayTcpController()
{
    /**
      Cleanup relayTcpSocket
    */
    if (m_relayTcpSocket.isOpen()) {
        m_relayTcpSocket.close();
    }
}

void RelayTcpController::slot_sendHandshake()
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
void RelayTcpController::slot_handleRelayTcpSocketErrorOccured(
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
    emit sig_relayBoardDisconnected();
}

void RelayTcpController::slot_handleRelayTcpSocketConnected()
{
    /* When Connected, Send the Handshake to initiate communication */
    QByteArray handshake(RELAY_BOARD_HANDSHAKE_REQUEST);
    m_relayTcpSocket.write(handshake);
}

void RelayTcpController::slot_handleRelayTcpSocketReadyRead()
{
    QByteArray response = m_relayTcpSocket.readAll();
    qDebug() << "Response Received" << response;
    emit sig_relayBoardConnected(response.toUShort());
}
