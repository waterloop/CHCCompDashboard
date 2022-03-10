#ifndef RELAYUDPCONTROLLER_H
#define RELAYUDPCONTROLLER_H

#include <QObject>
#include <QByteArray>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QHostAddress>
#include <QJsonDocument>
#include <QJsonObject>
#include "common.h"

using common::port_t;

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
    void slot_connectToRelayBoard(port_t udp_bind_port, port_t udp_connect_port);
    void slot_disconnectFromRelayBoard();
    void slot_updateMessageRequestedState(PodStates::e_PodState requested_state);
    void slot_updateMessageTimeStamp(qint64 timestamp);
    void slot_handleSocketTimer();

signals:
    void sig_dataReceived(QJsonObject podData);
    void sig_relayBoardTimedOut();

private:
    QUdpSocket m_relayBoardUdpSocket;
    port_t m_relayBoardUdpPort;
    QHostAddress m_relayBoardAddress;

    /// Message Fields
    qint64 m_timestamp;
    PodStates::e_PodState m_requested_state;
    QByteArray m_message; // Recomputed when the above changes

    /// Timer Fields
    QTimer m_timer;
    quint8 m_timeout_counter;

    void sendMessage();
    void updateMessage();
private slots:
    /**
     * @brief slot_handleRelayUdpSocketReadyRead
     * Called Each time a datagram is recieved on the
     * socket
     */
    void slot_handleRelayUdpSocketReadyRead();
};

#endif // RELAYUDPCONTROLLER_H
