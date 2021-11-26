#include "networkcontroller/networkcontroller.h"

NetworkController::NetworkController(PodController* podController, QObject *parent)
    : QObject(parent),
      m_relayTcpController(this),
      m_relayUdpController(this),
      m_relayBoardConnected(false)
{
    connect(&m_relayTcpController, &RelayTcpController::sig_relayBoardConnected,
            &m_relayUdpController, &RelayUdpController::slot_connectToRelayBoard);

    connect(&m_relayUdpController, &RelayUdpController::sig_dataReceived,
            podController, &PodController::slot_handlePodMessage);

    connect(&m_relayUdpController, &RelayUdpController::sig_relayBoardTimedOut, [=] () {
        this->disconnectFromRelayBoard();
    });

    connect(&m_relayTcpController, &RelayTcpController::sig_relayBoardConnected, [=]() {
        this->slot_updateConnectionStatus(true);
    });

    connect(&m_relayTcpController, &RelayTcpController::sig_disconnectMessageSuccess, [=]() {
        this->slot_updateConnectionStatus(false);
    });

    connect(podController, &PodController::sig_requestedStateChanged,
            &m_relayUdpController, &RelayUdpController::slot_updateMessageRequestedState);
}

NetworkController::~NetworkController() {}

void NetworkController::connectToRelayBoard()
{
    m_relayTcpController.slot_sendHandshake();
}

void NetworkController::disconnectFromRelayBoard()
{
    m_relayTcpController.slot_sendDisconnect();
}

bool NetworkController::getConnectionStatus() const
{
    return m_relayBoardConnected;
}

void NetworkController::slot_updateConnectionStatus(bool newConnectionStatus)
{
    if (m_relayBoardConnected != newConnectionStatus) {
        m_relayBoardConnected = newConnectionStatus;
        if (!m_relayBoardConnected) {
            m_relayUdpController.slot_disconnectFromRelayBoard();
        }
        emit sig_connectionStatusChanged(newConnectionStatus);
    }
}
