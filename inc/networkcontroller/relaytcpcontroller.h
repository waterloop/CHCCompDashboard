#ifndef RELAYTCPCONTROLLER_H
#define RELAYTCPCONTROLLER_H
#include <QObject>
#include <QTcpSocket>
#include <QtConcurrent/QtConcurrent>
#include <QString>
#include "common.h"

using common::port_t;

struct RelayTcpControllerConfig {
    port_t port;
    QString host;
};

class RelayTcpController : public QObject
{
    Q_OBJECT
public:
    explicit RelayTcpController(
                QObject* parent=nullptr,
                struct RelayTcpControllerConfig config={
                    RELAY_BOARD_DEFAULT_TCP_PORT,
                    QString(DEV_HOST)
                }
            );
    virtual ~RelayTcpController();

public slots:

    /*!
     * \brief RelayTcpController::slot_sendHandshake
     *
     * Queues the handshake request that will be sent when the
     * desktop connects to the relay board and then
     * triggers a connection to begin.
     */
    void slot_sendHandshake();
    void slot_sendMockCanRequest();

signals:
    /**
     * @brief sig_relayBoardConnected
     * Emmited when the network controller successfully
     * connects to the relay board.
     */
    void sig_relayBoardConnected(port_t udp_port);

    /**
     * @brief sig_relayBoardDisconnected
     * Emitted when the network controller disconnects from
     * the relay board
     */
    void sig_relayBoardDisconnected();


private:
    struct RelayTcpControllerConfig m_config;
    QTcpSocket m_relayTcpSocket;
    QByteArray m_message; // Message to be sent to the board on connection

    /**
     * @brief connectToBoard
     * Open the TCP port to the relay board
     */
    void connectToBoard();

private slots:
    /**
     * @brief slot_handleRelayTcpSocketError
     * @param socketError
     *
     * Handle any errors that are emmited from the relayTcpSocket
     */
    void slot_handleRelayTcpSocketErrorOccured(QAbstractSocket::SocketError socketError);

    /**
     * @brief slot_handleRelayTcpSocketConnected
     *
     * Handle initial connection the tcp socket on the
     * relay board
     */
    void slot_handleRelayTcpSocketConnected();

    /**
     * @brief slot_handleRelayTcpSocketReadReady
     * Handle Data comming into the TcpSocket
     */
    void slot_handleRelayTcpSocketReadyRead();
};
#endif // RELAYTCPCONTROLLER_H
