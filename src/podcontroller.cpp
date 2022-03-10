#include "inc/podcontroller.h"
#include <QDebug>

PodController::PodController(QObject *parent) : QObject(parent),
    m_bmsData(new BmsModel(this)),
    m_mcData(new MotorControlModel(this)),
    m_torchic1(new TorchicModel(this)),
    m_torchic2(new TorchicModel(this)),
    m_pressureHigh(new PressureSensorModel(INITIAL_PRESSURE_HIGH, PRESURE_TIMEOUT_MS, this)),
    m_pressureLow1(new PressureSensorModel(INITIAL_PRESSURE_LOW, PRESURE_TIMEOUT_MS, this)),
    m_pressureLow2(new PressureSensorModel(INITIAL_PRESSURE_LOW, PRESURE_TIMEOUT_MS, this)),
    m_liveData(this),
    m_currentState(PodStates::e_PodState::Resting),
    m_fieldHash()
{
    m_fieldHash.insert(QString("current_state"), FieldName::CURRENT_STATE);
    m_fieldHash.insert(QString("pending_next_state"), FieldName::PENDING_NEXT_STATE);
    m_fieldHash.insert(QString("errno"), FieldName::ERRNO);
    m_fieldHash.insert(QString("telemetry"), FieldName::TELEMETRY);
    m_fieldHash.insert(QString("telemetry_timestamp"), FieldName::TELEMETRY_TIMESTAMP);
    m_fieldHash.insert(QString("recovering"), FieldName::RECOVERING);
    m_fieldHash.insert(QString("speed"), FieldName::SPEED);
    m_fieldHash.insert(QString("battery_pack_voltage"), FieldName::BATTERY_PACK_VOLTAGE);
    m_liveData.insertData(*m_bmsData);

    connect(this, &PodController::sig_currentStateChanged,
            this, &PodController::sig_transitioningChanged);

    connect(this, &PodController::sig_requestedStateChanged,
            this, &PodController::sig_transitioningChanged);

    // Pass data to m_mcData
    connect(this,       &PodController::sig_podSpeedAvailable,
            m_mcData, &MotorControlModel::slot_podSpeedReceived);

    // Forward Updates from mcData to QML
    connect(m_mcData, &MotorControlModel::sig_podSpeedUpdated,
            this, &PodController::sig_mcDataChanged);
    connect(m_mcData, &MotorControlModel::sig_bateryVoltageUpdated ,
            this, &PodController::sig_mcDataChanged);
    connect(m_mcData, &MotorControlModel::sig_batteryCurrentUpdated,
            this, &PodController::sig_mcDataChanged);
    connect(m_mcData, &MotorControlModel::sig_igbtTemperatureUpdated,
            this, &PodController::sig_mcDataChanged);
    connect(m_mcData, &MotorControlModel::sig_motorVoltageUpdated,
            this, &PodController::sig_mcDataChanged);

    // Pass Data to torchics
    connect(this, &PodController::sig_torchic1DataAvailable,
            m_torchic1, &TorchicModel::slot_temperaturesAvailable);
    connect(this, &PodController::sig_torchic2DataAvailable,
            m_torchic2, &TorchicModel::slot_temperaturesAvailable);

    // Forward Updates from torchics to QML
    connect(m_torchic1, &TorchicModel::sig_temperatureUpdated,
            this, &PodController::sig_torchic1Changed);
    connect(m_torchic2, &TorchicModel::sig_temperatureUpdated,
            this, &PodController::sig_torchic2Changed);
}

PodController::~PodController()
{
    delete m_mcData;
    delete m_bmsData;
}

LiveDataModel* PodController::getLiveData()
{
    return &m_liveData;
}

bool PodController::isTransitioning() const
{
    return m_currentState == m_requestedState;
}

PodStates::e_PodState PodController::getCurrentState() const
{
    return m_currentState;
}

PodStates::e_PodState PodController::getRequestedState() const
{
    return m_requestedState;
}

void PodController::setCurrentState(const PodStates::e_PodState &currentState)
{
    if (m_currentState != currentState) {
        qDebug() << "Setting Current State to " << currentState;
        m_currentState = currentState;
        emit sig_currentStateChanged(currentState);
    }
}

void PodController::setRequestedState(const PodStates::e_PodState &requestedState)
{
    if (m_requestedState != requestedState) {
        qDebug() << "Setting RequestedState" << requestedState;
        m_requestedState = requestedState;
        emit sig_requestedStateChanged(requestedState);
    }
}

/**
 * @brief PodController::slot_handlePodMessage
 * @param podMessage
 * This slot handles the messages that the pod sends to the desktop
 * This includes parsing the telemetry data and passing it along to the
 * relavant data models which store and track the data.
 */
void PodController::slot_handlePodMessage(QJsonObject podMessage)
{
//    qDebug() << "Received Message" << podMessage;
    for (QString key : podMessage.keys())
    {
        if (!m_fieldHash.contains(key)) {
            qDebug() << "ERROR: Unknown Key found in podState. This may be a sign that the fieldhash is no longer complete\nKey Received: " << key;
            continue;
        }
        switch (m_fieldHash.value(key)) {
        case CURRENT_STATE: {
            QJsonValue value = podMessage.value(key);
            qDebug() << "Current State" << value;
            if (value.isDouble()) {
                int default_value{static_cast<int>(PodStates::e_PodState::Invalid)};
                setCurrentState(PodStates::from_int(value.toInt(default_value)));
            } else {
                setCurrentState(PodStates::e_PodState::Invalid);
            }
        }break;
        case ERRNO: {
            // TODO: Impliment
//            qDebug() << "Errno Value in Pod Message: " << podMessage.value(key);
        }break;
        case PENDING_NEXT_STATE: {
            // Handle Pending Next state
        }break;
        case RECOVERING: {
            QJsonValue value = podMessage.value(key);
            if (value.isBool() && value.toBool()) {

            }
        }break;
        case TELEMETRY: {
            QJsonValue value = podMessage.value(key);
            if (value.isObject()) {
                QJsonObject telemetry = value.toObject();
                for (const QString &key : telemetry.keys())
                {
                    switch (m_fieldHash.value(key)) {
                    case SPEED: {
                        QJsonValue val = telemetry.value(key);
                        if (val.isDouble()) {
                            emit sig_podSpeedAvailable(val.toInt());
                        } else {
                            qDebug() << "Error: Received a non numeric value for Pod speed\nValue Received: " << val;
                        }
                    } break;
                    case BATTERY_PACK_VOLTAGE: {
                        QJsonValue val = telemetry.value(key);
                        qDebug() << "BATTERY_PACK_VOLTAGE" << val;
                    }break;
                    default:
                        // qDebug() << "ERROR: Unhandled Key in Telemetry Data\nKey Received: " << key;
                        break;
                    }
                }
            } else if (value.isNull()) {
            } else {
                qDebug() << "ERROR: Telemetry Data received was not an object and was not null";
            }
        }break;
        case TELEMETRY_TIMESTAMP: {}break;
        default:
            qDebug() << "ERROR: Found a key that was not expected at the top level of the hierarchy.\nKey Found: " << key;
        }
    }
}
