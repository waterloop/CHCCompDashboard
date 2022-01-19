#include "networkcontroller/networkcontroller.h"
#include <QDebug>
#include <QRegularExpression>

QRegularExpression okMessage("^OK ");
QRegularExpression disconnectedMessage("^DISCONNECTED");
QRegularExpression errorMessage("^ERROR ");

RelayTcpController::RelayTcpController(QObject* parent, struct RelayTcpControllerConfig config)
    : QObject(parent),
      m_config(config),
      m_relayTcpSocket(this)

{
    /// Connect the relayTcpSocket signals to
    /// their respective signal handlers
    connect(&m_relayTcpSocket, &QAbstractSocket::errorOccurred,
            this, &RelayTcpController::slot_handleRelayTcpSocketErrorOccured);

    connect(&m_relayTcpSocket, &QAbstractSocket::connected,
            this, &RelayTcpController::slot_handleRelayTcpSocketConnected);

    connect(&m_relayTcpSocket, &QAbstractSocket::readyRead,
            this, &RelayTcpController::slot_handleRelayTcpSocketReadyRead);
    /// END
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
    /**
      * TODO: setup some type of mutual exclusion on the
      * m_message variable so that it cannot be changed
      * before it is sent
      */
    m_message = RELAY_BOARD_HANDSHAKE_REQUEST;
    connectToBoard();
}


void RelayTcpController::slot_sendMockCanRequest()
{
    m_message = RELAY_BOARD_MOCK_CAN_REQUEST;
    connectToBoard();
}

void RelayTcpController::slot_sendDisconnect()
{
    m_message = RELAY_BOARD_DISCONNECT;
    connectToBoard();
}

void RelayTcpController::connectToBoard()
{
#ifdef DEV_SANDBOX
    qDebug() << "Connecting to Relay board";
#endif
    m_relayTcpSocket.connectToHost(
                m_config.host,
                m_config.port,
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
        break;
    default:
        qDebug() << "Unknown Error Recieved from relayboardTcpSocket" << socketError;
        break;
    }
    emit sig_relayBoardDisconnected();
}

void RelayTcpController::slot_handleRelayTcpSocketConnected()
{
    /* When Connected, Send the Handshake to initiate communication */
    m_relayTcpSocket.write(m_message);
}

void RelayTcpController::slot_handleRelayTcpSocketReadyRead()
{
    QByteArray response = m_relayTcpSocket.readAll();
//    qDebug() << "Response Received" << response;
    QRegularExpressionMatch okMatch = okMessage.match(response);
    /// Full Message Will be of the Form "OK [0-9][0-9][0-9][0-9] | ERROR [a-zA-Z \.]* | DISCONNECTED"
    if (okMatch.hasMatch()) {
        response.remove(0, okMatch.capturedLength());
        emit sig_relayBoardConnected(response.toUShort());
    } else {
        QRegularExpressionMatch disconnectedMatch = disconnectedMessage.match(response);
        if (disconnectedMatch.hasMatch()) {
            emit sig_disconnectMessageSuccess();
        }

        QRegularExpressionMatch errorMatch = errorMessage.match(response);
        if (errorMatch.hasMatch()) {
            QString errorMessage = QString(response).remove("ERROR ");
            emit sig_relayBoardConnectionError(errorMessage);
        }
    }
}
