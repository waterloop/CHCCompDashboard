#include "inc/networkcontroller.h"

NetworkController::NetworkController(QObject *parent)
    : QObject(parent),
      m_relayTcpController(this),
      m_relayUdpController(this)
{
    connect(&m_relayTcpController, &RelayTcpController::sig_relayBoardConnected,
            &m_relayUdpController, &RelayUdpController::slot_connectToRelayBoard);
}

NetworkController::~NetworkController() {}

void NetworkController::connectToRelayBoard()
{
    m_relayTcpController.slot_sendHandshake();
}
