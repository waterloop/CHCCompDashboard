#include "inc/networkcontroller/relayudpcontroller.h"


/*********************************************
 *                                           *
 *                PUBLIC METHODS             *
 *                                           *
 *********************************************/

RelayUdpController::RelayUdpController(QObject *parent)
    : QObject(parent),
      m_relayBoardUdpSocket(this),
      m_relayBoardUdpPort(0), // Init in slot_connectToRelayBoard
      m_relayBoardAddress(DEV_HOST),
      m_timestamp(1), // If you make this 0, the relay board will not be able to handle it
      m_requested_state(PodStates::e_PodState::LowVoltage),
      m_timer(this),
      m_timeout_counter(0)
{
    updateMessage();
    connect(&m_relayBoardUdpSocket, &QUdpSocket::readyRead,
            this, &RelayUdpController::slot_handleRelayUdpSocketReadyRead);
}

RelayUdpController::~RelayUdpController() {}

/*********************************************
 *                                           *
 *                PUBLIC SLOTS               *
 *                                           *
 *********************************************/

void RelayUdpController::slot_connectToRelayBoard(port_t udp_port)
{
    m_relayBoardUdpPort = udp_port;
    m_relayBoardUdpSocket.bind(QHostAddress::AnyIPv4,
                          udp_port);
    qDebug() << "Bound on Port" << udp_port;
    connect(&m_timer, &QTimer::timeout, [=]() {
        this->sendMessage(m_message);
        this->m_timeout_counter++;
        if (this->m_timeout_counter == 10) {
            emit sig_relayBoardTimedOut();
        }
    });
    m_timer.start(2000);

#ifdef DEV_SANDBOX // Pingpong with the server
    qDebug() << "Bound on port:" << udp_port;
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=]() {
        qDebug() << "Sending Hello";
        this->sendMessage(QByteArray("Hello"));
    });
    timer->start(500); // This will leak memory if we're not careful
#endif
}

void RelayUdpController::slot_disconnectFromRelayBoard()
{
    disconnect(&m_timer, &QTimer::timeout, nullptr, nullptr);
}

void RelayUdpController::slot_updateMessageRequestedState(PodStates::e_PodState requested_state)
{
    m_requested_state = requested_state;
    updateMessage();
}

void RelayUdpController::slot_updateMessageTimeStamp(qint64 timestamp)
{
    m_timestamp = timestamp;
    updateMessage();
}


/*********************************************
 *                                           *
 *                Private Methods            *
 *                                           *
 *********************************************/

void RelayUdpController::sendMessage(const QByteArray message) {
    QNetworkDatagram datagram(
                    message,
                    m_relayBoardAddress,
                    RELAY_BOARD_DEFAULT_PORT);
//    qDebug() << "Sending Message" << message;
//    qDebug() << "Address: " << m_relayBoardAddress << ":" << m_relayBoardUdpPort;
    m_relayBoardUdpSocket.writeDatagram(datagram);
}

/**
 * @brief RelayUdpController::updateMessage
 * Called After new data is received. Builds a new byte array to be sent in the next message
 */
void RelayUdpController::updateMessage()
{
    QJsonObject object;
    object.insert("requested_state", QJsonValue::fromVariant((int)m_requested_state));
    object.insert("most_recent_timestamp", QJsonValue::fromVariant((int)m_timestamp));
    m_message = QJsonDocument(object).toJson();
}


/*********************************************
 *                                           *
 *                Private SLOTS              *
 *                                           *
 *********************************************/

void RelayUdpController::slot_handleRelayUdpSocketReadyRead()
{
    while (m_relayBoardUdpSocket.hasPendingDatagrams())
    {
        QNetworkDatagram datagram = m_relayBoardUdpSocket.receiveDatagram();
        m_timeout_counter = 0; // reset timeout counter when we receive a message
        QByteArray data = datagram.data();
//        qDebug() << "Received Data from RelayBoard UDP:" << data;
        QJsonParseError error;
        QJsonDocument jsonData = QJsonDocument::fromJson(data, &error);
        if (jsonData.isObject()) {
            QJsonObject object = jsonData.object();
            if (object.contains("telemetry_timestamp")) {
                QJsonValue ts = object.value("telemetry_timestamp");
                if (ts.isDouble()) {
                    slot_updateMessageTimeStamp(ts.toInt());
                }
            }
            if (parent() != nullptr && parent()->property("relayBoardConnected").toBool()) {
                sendMessage(m_message);
            }
            emit sig_dataReceived(object);
        } else {
//            qDebug() << "Error: Data received was not a Object. Error:" << error.errorString();
        }
    }
}













