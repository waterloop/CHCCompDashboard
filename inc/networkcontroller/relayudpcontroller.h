#ifndef RELAYUDPCONTROLLER_H
#define RELAYUDPCONTROLLER_H

#include <QObject>
#include <QByteArray>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QHostAddress>
#include "../common.h"

class RelayUdpController : public QObject
{
    Q_OBJECT
public:
    explicit RelayUdpController(QObject *parent = nullptr);
    virtual ~RelayUdpController();

public slots:
    /**
     * @brief slot_connectToRelayBoard
     * @param udp_port
     * Attempts to connect to a udp port on the relay board
     * At a given port
     */
    void slot_connectToRelayBoard(port_t udp_port);

signals:
    void sig_dataReceived(QByteArray data);

private:
    QUdpSocket m_relayBoardUdpSocket;
    port_t m_relayBoardUdpPort;
    QHostAddress m_relayBoardAddress;

    void sendMessage(const QByteArray message);

private slots:
    /**
     * @brief slot_handleRelayUdpSocketReadyRead
     * Called Each time a datagram is recieved on the
     * socket
     */
    void slot_handleRelayUdpSocketReadyRead();
};

#endif // RELAYUDPCONTROLLER_H
