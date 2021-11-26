#ifndef NETWORKCONTROLLER_H
#define NETWORKCONTROLLER_H
#include <QObject>
#include "common.h"
#include "networkcontroller/relaytcpcontroller.h"
#include "networkcontroller/relayudpcontroller.h"
#include "podcontroller.h"


/*!
 * \brief The NetworkController class
 * The NetworkController is responsible for communicating with
 * the relay board over the network and emiting signals when messages are received
 */
class NetworkController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool relayBoardConnected READ getConnectionStatus NOTIFY sig_connectionStatusChanged)
public:
    explicit NetworkController(PodController* podController, QObject* parent = nullptr);
    ~NetworkController();

    /**
     * @brief connectToRelayBoard
     * This is a non-blocking function which initiates a
     * connection to the relay board.
     */
    Q_INVOKABLE void connectToRelayBoard();
    Q_INVOKABLE void disconnectFromRelayBoard();

    bool getConnectionStatus() const;

private:
    RelayTcpController m_relayTcpController;
    RelayUdpController m_relayUdpController;

    /// m_relayBoardConnected Tracks the logical connection between the Pod and the desktop
    /// When "connected": The UDP controller will be actively sending messages
    /// When "disconnected": The UDP controller does not actively send messages
    bool m_relayBoardConnected;

public slots:
    void slot_updateConnectionStatus(bool newConnectionStatus);
signals:
    void sig_connectionStatusChanged(bool connectionStatus);
};

#endif // NETWORKCONTROLLER_H
