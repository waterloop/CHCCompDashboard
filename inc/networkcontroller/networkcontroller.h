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
public:
    explicit NetworkController(PodController* podController, QObject* parent = nullptr);
    ~NetworkController();

    /**
     * @brief connectToRelayBoard
     * This is a non-blocking function which initiates a
     * connection to the relay board.
     */
    Q_INVOKABLE void connectToRelayBoard();

private:
    RelayTcpController m_relayTcpController;
    RelayUdpController m_relayUdpController;
};

#endif // NETWORKCONTROLLER_H
