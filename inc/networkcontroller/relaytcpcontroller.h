#ifndef RELAYTCPCONTROLLER_H
#define RELAYTCPCONTROLLER_H
#include <QObject>
#include <QTcpSocket>
#include <QtConcurrent/QtConcurrent>
#include "../common.h"

class RelayTcpController : public QObject
{
    Q_OBJECT
public:
    explicit RelayTcpController(QObject* parent=nullptr);
    virtual ~RelayTcpController();

public slots:
    void slot_sendHandshake();

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
    QTcpSocket m_relayTcpSocket;

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
