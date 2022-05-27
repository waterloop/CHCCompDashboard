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

void RelayUdpController::slot_connectToRelayBoard(port_t udp_bind_port, port_t udp_connect_port)
{
    m_relayBoardUdpPort = udp_connect_port;
    if (!m_relayBoardUdpSocket.bind(QHostAddress::AnyIPv4,
                          udp_bind_port)) {
        qDebug() << "Failed to bind UDP socket";
        emit sig_relayBoardTimedOut();
        return;
    }
    qDebug() << "UDP Socket Bound on Port" << udp_bind_port << ". Sending Messages on :" << udp_connect_port;
    connect(&m_timer, &QTimer::timeout, this, &RelayUdpController::slot_handleSocketTimer);
    m_timer.start(2000);
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

/**
 * @brief RelayUdpController::slot_handleSocketTimer
 * Increments the Timeout counter and sends another message
 */
void RelayUdpController::slot_handleSocketTimer()
{
    sendMessage();
    m_timeout_counter++;
    if (m_timeout_counter >= 10) {
        emit sig_relayBoardTimedOut();
    }
}


/*********************************************
 *                                           *
 *                Private Methods            *
 *                                           *
 *********************************************/

void RelayUdpController::sendMessage() {
    QNetworkDatagram datagram(
                    m_message,
                    m_relayBoardAddress,
                    m_relayBoardUdpPort);
//    qDebug() << "Sending UDP Message" << message;
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
//    qDebug() << " Updated Message " << m_message;
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
                sendMessage();
            }
            emit sig_dataReceived(object);
        } else {
//            qDebug() << "Error: Data received was not a Object. Error:" << error.errorString();
        }
    }
}













