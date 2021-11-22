#include "networkcontroller/networkcontroller.h"

NetworkController::NetworkController(PodController* podController, QObject *parent)
    : QObject(parent),
      m_relayTcpController(this),
      m_relayUdpController(this)
{
    connect(&m_relayTcpController, &RelayTcpController::sig_relayBoardConnected,
            &m_relayUdpController, &RelayUdpController::slot_connectToRelayBoard);

    connect(&m_relayUdpController, &RelayUdpController::sig_dataReceived,
            podController, &PodController::slot_handlePodMessage);

}

NetworkController::~NetworkController() {}

void NetworkController::connectToRelayBoard()
{
    m_relayTcpController.slot_sendHandshake();
}
