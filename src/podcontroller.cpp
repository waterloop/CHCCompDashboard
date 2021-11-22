#include "inc/podcontroller.h"
#include <QDebug>

PodController::PodController(QObject *parent) : QObject(parent),
    m_bmsData(new BmsModel(this)),
    m_mcData(new MotorControlModel(this)),
    m_liveData(this),
    m_currentState(e_PodState::Resting),
    m_fieldHash()
{
    m_fieldHash.insert(QString("current_state"), FieldName::CURRENT_STATE);
    m_fieldHash.insert(QString("pending_next_state"), FieldName::PENDING_NEXT_STATE);
    m_fieldHash.insert(QString("errno"), FieldName::ERRNO);
    m_fieldHash.insert(QString("telemetry"), FieldName::TELEMETRY);
    m_fieldHash.insert(QString("telemetry_timestamp"), FieldName::TELEMETRY_TIMESTAMP);
    m_fieldHash.insert(QString("recovering"), FieldName::RECOVERING);
    m_fieldHash.insert(QString("speed"), FieldName::SPEED);
    m_liveData.insertData(*m_bmsData);

    connect(this, &PodController::sig_currentStateChanged,
            this, &PodController::sig_transitioningChanged);

    connect(this, &PodController::sig_requestedStateChanged,
            this, &PodController::sig_transitioningChanged);

    // Connections to m_mcData
    connect(this,       &PodController::sig_podSpeedAvailable,
            m_mcData, &MotorControlModel::slot_podSpeedReceived);
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

e_PodState PodController::getCurrentState() const
{
    return m_currentState;
}

common::e_PodState PodController::getRequestedState() const
{
    return m_requestedState;
}

void PodController::setCurrentState(const e_PodState &currentState)
{
    qDebug() << "Setting Current State to " << currentState;
    if (m_currentState != currentState) {
        m_currentState = currentState;
        emit sig_currentStateChanged(currentState);
    }
}

void PodController::setRequestedState(const common::e_PodState &requestedState)
{
    if (m_requestedState != requestedState) {
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
    for (QString key : podMessage.keys())
    {
        if (!m_fieldHash.contains(key)) {
            qDebug() << "ERROR: Unknown Key found in podState. This may be a sign that the fieldhash is no longer complete\nKey Received: " << key;
            continue;
        }
        switch (m_fieldHash.value(key)) {
        case CURRENT_STATE: {
            QJsonValue value = podMessage.value(key);
            if (value.isDouble()) {
                int default_value{static_cast<int>(e_PodState::Invalid)};
                setCurrentState(common::from_int(value.toInt(default_value)));
            } else {
                setCurrentState(e_PodState::Invalid);
            }
        }break;
        case ERRNO: {
            // TODO: Impliment
            qDebug() << "Errno Value in Pod Message: " << podMessage.value(key);
        }break;
        case PENDING_NEXT_STATE: {
            QJsonValue value = podMessage.value(key);
            if (value.isDouble()) {
                int default_value{static_cast<int>(e_PodState::Invalid)};
                setRequestedState(common::from_int(value.toInt(default_value)));
            } else {
                setRequestedState(e_PodState::Invalid);
            }
        }break;
        case RECOVERING: {
            // TODO Implement
        }break;
        case TELEMETRY: {
            QJsonValue value = podMessage.value(key);
            if (value.isObject()) {
                QJsonObject telemetry = value.toObject();
                for (QString key : telemetry.keys())
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
                    default:
                        qDebug() << "ERROR: Unhandled Key in Telemetry Data\nKey Received: " << key;
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

e_PodState common::from_int(int val)
{
    switch (val) {
    case 0:
        return e_PodState::Resting;
    case 1:
        return e_PodState::LowVolatage;
    case 2:
        return e_PodState::Armed;
    case 3:
        return e_PodState::AutoPilot;
    case 4:
        return e_PodState::Braking;
    case 5:
        return e_PodState::EmergencyBrake;
    case 6:
        return e_PodState::SystemFailure;
    case 7:
        return e_PodState::ManualOperationWaiting;
    case 8:
        return e_PodState::Accellerating;
    case 9:
        return e_PodState::AtSpeed;
    case 10:
        return e_PodState::Decelerating;
    default:
        return e_PodState::Invalid;
    }
}
