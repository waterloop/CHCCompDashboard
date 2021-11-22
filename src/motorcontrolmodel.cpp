#include "inc/motorcontrolmodel.h"

MotorControlModel::MotorControlModel(QObject *parent)
    : QObject(parent),
      m_igbtTemperature(INITIAL_IGBT_TEMP, IGBT_TEMP_TIMEOUT_MS, this),
      m_podSpeed(INITIAL_POD_SPEED, POD_SPEED_TIMEOUT_MS, this),
      m_batteryCurrent(INITIAL_BATTERY_CURRRENT, BATTERY_CURRENT_TIMEOUT_MS, this),
      m_motorVoltage(INITIAL_MOTOR_VOLTAGE, MOTOR_VOLTAGE_TIMEOUT_MS, this),
      m_batteryVoltage(INITIAL_BATTERY_VOLTAGE, BATTERY_VOLTAGE_TIMEOUT_MS, this),
      m_igbtTemperatureSafeRange({ .max = IGBT_MAX_TEMP, .min = IGBT_MIN_TEMP}),
      m_podSpeedSafeRange({ .max = POD_SPEED_MAX, .min = POD_SPEED_MIN}),
      m_batteryCurrentSafeRange({.max = BATTERY_MAX_CURRENT, .min = BATTERY_MIN_CURRENT}),
      m_motorVoltageSafeRange({.max = MOTOR_MAX_VOLTAGE, .min = MOTOR_MIN_VOLTAGE}),
      m_batteryVoltageSafeRange({ .max = BATTERY_MAX_VOLTAGE, .min = BATTERY_MIN_VOLTAGE})
{

}

QList<QSharedPointer<LiveDataNode> > MotorControlModel::enumerate() const
{
    QList<QSharedPointer<LiveDataNode>> responseList;
    return responseList;
}

/*****************
 *   OPERATORS   *
 *****************/

MotorControlModel &MotorControlModel::operator=(const MotorControlModel &other)
{
    if (this == &other) return *this;
    this->m_batteryCurrent = other.getBatteryCurrent();
    this->m_batteryVoltage = other.getBatteryVoltage();
    this->m_igbtTemperature = other.getIgbtTemperature();
    this->m_motorVoltage = other.getMotorVoltage();
    this->m_podSpeed = other.getPodSpeed();
    return *this;
}

bool MotorControlModel::operator==(const MotorControlModel &other) const
{
    return (
        this->getBatteryCurrent() == other.getBatteryCurrent() &&
        this->getBatteryVoltage() == other.getBatteryVoltage() &&
        this->getIgbtTemperature() == other.getIgbtTemperature() &&
        this->getMotorVoltage() == other.getMotorVoltage() &&
        this->getPodSpeed() == other.getPodSpeed()
                );
}

bool MotorControlModel::operator!=(const MotorControlModel &other) const
{
 return !(*this == other);
}

/*****************
 *   GETTERS     *
 *****************/

float MotorControlModel::getPodSpeed() const
{
    return m_podSpeed.getState().toFloat();
}

float MotorControlModel::getBatteryCurrent() const
{
    return m_batteryCurrent.getState().toFloat();
}

float MotorControlModel::getIgbtTemperature() const
{
    return m_igbtTemperature.getState().toFloat();
}

float MotorControlModel::getMotorVoltage() const
{
    return m_motorVoltage.getState().toFloat();
}

float MotorControlModel::getBatteryVoltage() const
{
    return m_batteryVoltage.getState().toFloat();
}

/*************
 *   SLOTS   *
 *************/
void MotorControlModel::slot_podSpeedReceived(float newPodSpeed)
{
    bool newValue = newPodSpeed != this->getPodSpeed();
    // we call updateState no matter what because it will
    // reset the timer. Even if the value is the same
    this->m_podSpeed.updateState(newPodSpeed);
    if (newValue) {
        // only notify others if the value has actually changed though
        emit sig_podSpeedUpdated(newPodSpeed);
    }
}
