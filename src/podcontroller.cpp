#include "inc/podcontroller.h"
#include <QDebug>

PodController::PodController(QObject *parent) : QObject(parent),
    m_bmsData(new BmsModel(this)),
    m_mcData(new MotorControlModel(this)),
    m_torchic1(new TorchicModel(this)),
    m_torchic2(new TorchicModel(this)),
    m_pressureHigh(new PressureSensorModel(QString("High Pressure"), INITIAL_PRESSURE_HIGH, OperationalEnvelope{ .max= MAX_PRESSURE_HIGH, .min=MIN_PRESSURE_HIGH }, this)),
    m_pressureLow1(new PressureSensorModel(QString("Low Pressure 1"), INITIAL_PRESSURE_LOW, OperationalEnvelope{ .max= MAX_PRESSURE_LOW, .min=MIN_PRESSURE_LOW }, this)),
    m_pressureLow2(new PressureSensorModel(QString("Low Pressure 2"), INITIAL_PRESSURE_LOW, OperationalEnvelope{ .max= MAX_PRESSURE_LOW, .min=MIN_PRESSURE_LOW }, this)),
    m_liveData(this),
    m_currentState(PodStates::e_PodState::Resting),
    m_fieldHash()
{
    /* Build field name map */
    m_fieldHash.insert(QString("current_state"), FieldName::CURRENT_STATE);
    m_fieldHash.insert(QString("pending_next_state"), FieldName::PENDING_NEXT_STATE);
    m_fieldHash.insert(QString("errno"), FieldName::ERRNO);
    m_fieldHash.insert(QString("telemetry"), FieldName::TELEMETRY);
    m_fieldHash.insert(QString("telemetry_timestamp"), FieldName::TELEMETRY_TIMESTAMP);
    m_fieldHash.insert(QString("recovering"), FieldName::RECOVERING);
    m_fieldHash.insert(QString("speed"), FieldName::SPEED);
    m_fieldHash.insert(QString("battery_pack_current"), FieldName::BATTERY_PACK_CURRENT);
    m_fieldHash.insert(QString("average_cell_temperature"), FieldName::AVERAGE_CELL_TEMPERATURE);
    m_fieldHash.insert(QString("igbt_temperature"), FieldName::IGBT_TEMPERATURE);
    m_fieldHash.insert(QString("motor_voltage"), FieldName::MOTOR_VOLTAGE);
    m_fieldHash.insert(QString("battery_pack_voltage"), FieldName::BATTERY_PACK_VOLTAGE);
    m_fieldHash.insert(QString("buck_temperature"), FieldName::BUCK_TEMPERATURE);
    m_fieldHash.insert(QString("bms_current"), FieldName::BMS_CURRENT);
    m_fieldHash.insert(QString("link_cap_voltage"), FieldName::LINK_CAP_VOLTAGE);
    m_fieldHash.insert(QString("motor_current"), FieldName::MOTOR_CURRENT);
    m_fieldHash.insert(QString("battery_current"), FieldName::BATTERY_CURRENT);
    m_fieldHash.insert(QString("battery_voltage"), FieldName::BATTERY_VOLTAGE);
    m_fieldHash.insert(QString("torchic_1"), FieldName::TORCHIC_1);
    m_fieldHash.insert(QString("torchic_2"), FieldName::TORCHIC_2);
    m_fieldHash.insert(QString("pressure_high"), FieldName::PRESSURE_HIGH);
    m_fieldHash.insert(QString("pressure_low_1"), FieldName::PRESSURE_LOW_1);
    m_fieldHash.insert(QString("pressure_low_2"), FieldName::PRESSURE_LOW_2);
    /* Setup the live data model */
    m_liveData.insertData(*m_bmsData);
    m_liveData.insertData(*m_mcData);
    m_liveData.insertData(*m_torchic1);
    m_liveData.insertData(*m_torchic2);
    m_liveData.insertData(*m_pressureHigh);
    m_liveData.insertData(*m_pressureLow1);
    m_liveData.insertData(*m_pressureLow2);

    /* Connections */
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


    // Send data to pressure sensor models
    connect(this, &PodController::sig_pressureHighDataAvailable,
            m_pressureHigh, &PressureSensorModel::slot_updatePressure);

    connect(this, &PodController::sig_pressureLow1DataAvailable,
            m_pressureLow1, &PressureSensorModel::slot_updatePressure);

    connect(this, &PodController::sig_pressureLow2DataAvailable,
            m_pressureLow2, &PressureSensorModel::slot_updatePressure);

    // Forward Data to QML from pressure Sensors
    connect(m_pressureHigh, &PressureSensorModel::sig_pressureUpdated,
            this, &PodController::sig_pressureHighChanged);
    connect(m_pressureLow1, &PressureSensorModel::sig_pressureUpdated,
            this, &PodController::sig_pressureLow1Changed);
    connect(m_pressureLow2, &PressureSensorModel::sig_pressureUpdated,
            this, &PodController::sig_pressureLow2Changed);
}

PodController::~PodController()
{
    delete m_mcData;
    delete m_bmsData;
    delete m_torchic1;
    delete m_torchic2;
    delete m_pressureLow1;
    delete m_pressureLow2;
    delete m_pressureHigh;
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
//        qDebug() << "Setting Current State to " << currentState;
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
//            qDebug() << "Current State" << value;
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
                    case BATTERY_PACK_CURRENT: {
                        QJsonValue val = telemetry.value(key);
                        if (val.isDouble()) {
                            emit sig_batteryPackCurrentAvailable(val.toDouble());
                        } else {
                            qDebug() << "Error: Received a non numeric value for Pod speed\nValue Received: " << val;
                        }
                    } break;
                    case AVERAGE_CELL_TEMPERATURE: {
                        QJsonValue val = telemetry.value(key);
                        if (val.isDouble()) {
                            emit sig_averageCellTemperatureAvailable(val.toDouble());
                        } else {
                            qDebug() << "Error: Received a non numeric value for Pod speed\nValue Received: " << val;
                        }
                    } break;
                    case IGBT_TEMPERATURE: {
                        QJsonValue val = telemetry.value(key);
                        if (val.isDouble()) {
                            emit sig_igbtTempAvailable(val.toDouble());
                        } else {
                            qDebug() << "Error: Received a non numeric value for Pod speed\nValue Received: " << val;
                        }
                    } break;
                    case MOTOR_VOLTAGE: {
                        QJsonValue val = telemetry.value(key);
                        if (val.isDouble()) {
                            emit sig_motorVoltageAvailable(val.toDouble());
                        } else {
                            qDebug() << "Error: Received a non numeric value for Pod speed\nValue Received: " << val;
                        }
                    } break;
                    case BUCK_TEMPERATURE: {
                        QJsonValue val = telemetry.value(key);
                        if (val.isDouble()) {
                            emit sig_buckTemperatureAvailable(val.toDouble());
                        } else {
                            qDebug() << "Error: Received a non numeric value for Pod speed\nValue Received: " << val;
                        }
                    } break;
                    case BMS_CURRENT: {
                        QJsonValue val = telemetry.value(key);
                        if (val.isDouble()) {
                            emit sig_bmsCurrentAvailable(val.toDouble());
                        } else {
                            qDebug() << "Error: Received a non numeric value for Pod speed\nValue Received: " << val;
                        }
                    } break;
                    case LINK_CAP_VOLTAGE: {
                        QJsonValue val = telemetry.value(key);
                        if (val.isDouble()) {
                            emit sig_linkCapVoltageAvailable(val.toDouble());
                        } else {
                            qDebug() << "Error: Received a non numeric value for Pod speed\nValue Received: " << val;
                        }
                    } break;
                    case MOTOR_CURRENT: {
                        QJsonValue val = telemetry.value(key);
                        if (val.isDouble()) {
                            emit sig_motorCurrentAvailable(val.toDouble());
                        } else {
                            qDebug() << "Error: Received a non numeric value for Pod speed\nValue Received: " << val;
                        }
                    } break;
                    case BATTERY_CURRENT: {
                        QJsonValue val = telemetry.value(key);
                        if (val.isDouble()) {
                            emit sig_batteryCurrentAvailable(val.toDouble());
                        } else {
                            qDebug() << "Error: Received a non numeric value for Pod speed\nValue Received: " << val;
                        }
                    } break;
                    case BATTERY_VOLTAGE: {
                        QJsonValue val = telemetry.value(key);
                        if (val.isDouble()) {
                            emit sig_batteryVoltageAvailable(val.toDouble());
                        } else {
                            qDebug() << "Error: Received a non numeric value for Pod speed\nValue Received: " << val;
                        }
                    } break;
                    case TORCHIC_1: {
                        QJsonValue val = telemetry.value(key);
                        qDebug() << "Torchic 1" << val;
                        if (val.isArray()) {
                            QJsonArray a = val.toArray();
                            emit sig_torchic1DataAvailable(a.at(0).toDouble(), a.at(1).toDouble());
                        } else {
                            qDebug() << "Error: Received a non numeric value for Pod speed\nValue Received: " << val;
                        }
                    } break;
                    case TORCHIC_2: {
                        QJsonValue val = telemetry.value(key);
                        if (val.isArray()) {
                            QJsonArray a = val.toArray();
                            emit sig_torchic2DataAvailable(a.at(0).toDouble(), a.at(1).toDouble());
                        } else {
                            qDebug() << "Error: Received a non numeric value for Pod speed\nValue Received: " << val;
                        }
                    } break;
                    case PRESSURE_HIGH: {
                        QJsonValue val = telemetry.value(key);
                        if (val.isDouble()) {
                            emit sig_pressureHighDataAvailable(val.toDouble());
                        } else {
                            qDebug() << "Error: Received a non numeric value for Pod speed\nValue Received: " << val;
                        }
                    } break;
                    case PRESSURE_LOW_1: {
                        QJsonValue val = telemetry.value(key);
                        if (val.isDouble()) {
                            emit sig_pressureLow1DataAvailable(val.toDouble());
                        } else {
                            qDebug() << "Error: Received a non numeric value for Pod speed\nValue Received: " << val;
                        }
                    } break;
                    case PRESSURE_LOW_2: {
                        QJsonValue val = telemetry.value(key);
                        if (val.isDouble()) {
                            emit sig_pressureLow2DataAvailable(val.toDouble());
                        } else {
                            qDebug() << "Error: Received a non numeric value for Pod speed\nValue Received: " << val;
                        }
                    } break;
                    case SPEED: {
                        QJsonValue val = telemetry.value(key);
                        qDebug() << "Pod speed" << val;
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
