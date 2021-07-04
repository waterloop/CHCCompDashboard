#ifndef NETWORKCONTROLLER_H
#define NETWORKCONTROLLER_H
#include <QObject>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QtConcurrent/QtConcurrent>
#include "common.h"

/*!
 * \brief The NetworkController class
 * The NetworkController is responsible for communicating with
 * the relay board over the network and emiting signals when messages are received
 */
class NetworkController : public QObject
{
    Q_OBJECT
public:
    explicit NetworkController(QObject* parent = nullptr);
    ~NetworkController();

public:
    /**
     * @brief connectToRelayBoard
     * This is a non-blocking function which initiates a
     * connection to the relay board.
     */
    Q_INVOKABLE void connectToRelayBoard();

signals:
    /**
     * @brief sig_relayBoardConnected
     * Emmited when the network controller successfully
     * connects to the relay board
     */
    void sig_relayBoardConnected();

    /**
     * @brief sig_relayBoardDisconnected
     * Emitted when the network controller disconnects from
     * the relay board
     */
    void sig_relayBoardDisconnected();


private:
    QTcpSocket m_relayTcpSocket;
    QUdpSocket m_relayUdpSocket;

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

#endif // NETWORKCONTROLLER_H
