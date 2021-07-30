#include "inc/bmsmodel.h"

BmsModel::BmsModel(QObject* parent)
    : QObject(parent),
      m_batteryPackCurrent(INITIAL_BATPACK_CURRENT, BATPACK_CURRENT_TIMEOUT_MS, this),
      m_batteryPackVoltage(INITIAL_BATPACK_VOLTAGE, BATPACK_VOLTAGE_TIMEOUT_MS, this),
      m_cellTemperature(INITIAL_CELL_TEMP, CELL_TEMP_TIMEOUT_MS, this),
      m_stateOfCharge(INITIAL_STATE_OF_CHARGE, STATE_OF_CHARGE_TIMEOUT_MS, this),
      m_buckTemperature(INITIAL_BUCK_TEMP, BUCK_TEMP_TIMEOUT_MS, this),
      m_bmsCurrent(INITIAL_BMS_CURRENT, BMS_CURRENT_TIMEOUT_MS, this),
      m_mcDcLinkCapacitorVoltage(INITIAL_DC_LINK_CAP_VOLTAGE, DC_LINK_CAP_VOLTAGE_TIMEOUT_MS, this),
      m_batterPackCurrentSafeRange({.max =  BATPACK_MAX_CURRENT, .min = BATPACK_MIN_CURRENT}),
      m_batterPackVoltageSafeRange({ .max = BATPACK_MAX_VOLTAGE, .min = BATPACK_MIN_VOLTAGE}),
      m_cellTemperatureSafeRange({.max = CELL_MAX_TEMP, .min = CELL_MIN_TEMP}),
      m_stateOfChargeSafeRange({.max = STATE_OF_CHARGE_MAX, .min = STATE_OF_CHARGE_MIN}),
      m_buckTemperatureSafeRange({.max = BUCK_MAX_TEMP, .min = BUCK_MIN_TEMP}),
      m_bmsCurrentSafeRange({.max = BMS_MAX_CURRENT, .min = BMS_MIN_CURRENT}),
      m_mcDcLinkCapacitorVoltageSafeRange({.max = DC_LINK_CAP_MAX_VOLTAGE, .min = DC_LINK_CAP_MIN_VOLTAGE})
{
    ///
    /// Connect each pod state's timer output to the health check failure
    /// signal. If any of them fail to receive a message within the specified
    /// time frame, then the sig_bmsHealthCheckFailure signal can be used
    /// to notify an operator
    ///
    connect(&m_batteryPackCurrent, &PodState<float>::sig_stateHealthCheckMissed,
            this, &BmsModel::sig_bmsHealthCheckFailure);
    connect(&m_batteryPackVoltage, &PodState<float>::sig_stateHealthCheckMissed,
            this, &BmsModel::sig_bmsHealthCheckFailure);
    connect(&m_cellTemperature, &PodState<float>::sig_stateHealthCheckMissed,
            this, &BmsModel::sig_bmsHealthCheckFailure);
    connect(&m_stateOfCharge, &PodState<float>::sig_stateHealthCheckMissed,
            this, &BmsModel::sig_bmsHealthCheckFailure);
    connect(&m_buckTemperature, &PodState<float>::sig_stateHealthCheckMissed,
            this, &BmsModel::sig_bmsHealthCheckFailure);
    connect(&m_bmsCurrent, &PodState<float>::sig_stateHealthCheckMissed,
            this, &BmsModel::sig_bmsHealthCheckFailure);
    connect(&m_mcDcLinkCapacitorVoltage, &PodState<float>::sig_stateHealthCheckMissed,
            this, &BmsModel::sig_bmsHealthCheckFailure);

}

///////////////////////////////////////////////////////////////////////////////
///
///                                 PUBLIC ACCESSORS
///
///////////////////////////////////////////////////////////////////////////////
float BmsModel::getBatteryPackCurrent() const
{
    return m_batteryPackCurrent.getState().toFloat();
}

float BmsModel::getBatteryPackVoltage() const
{
    return m_batteryPackVoltage.getState().toFloat();
}

float BmsModel::getCellTempurature() const
{
    return m_cellTemperature.getState().toFloat();
}

float BmsModel::getStateOfCharge() const
{
    return m_stateOfCharge.getState().toFloat();
}

float BmsModel::getBuckTemperature() const
{
    return m_buckTemperature.getState().toFloat();
}

float BmsModel::getBmsCurrent() const
{
    return m_bmsCurrent.getState().toFloat();
}

float BmsModel::getMcDcLinkCapacitorVoltage() const
{
    return m_mcDcLinkCapacitorVoltage.getState().toFloat();
}

///////////////////////////////////////////////////////////////////////////////
///
///                    Public LiveDataModelInput Methods
///
///////////////////////////////////////////////////////////////////////////////
QList<QSharedPointer<LiveDataNode>> BmsModel::enumerate() const
{
    QList<QSharedPointer<LiveDataNode>> responseList;
    responseList.append(QSharedPointer<LiveDataNode>(new LiveDataNode(QString("Battery Pack Current"), getBatteryPackCurrent(), common::AMP, m_batterPackCurrentSafeRange, &BmsModel::sig_batteryPackCurrentUpdated, this)));
    responseList.append(QSharedPointer<LiveDataNode>(new LiveDataNode(QString("Battery Pack Voltage"), getBatteryPackVoltage(), common::VOLT, m_batterPackVoltageSafeRange, &BmsModel::sig_batteryPackVoltageUpdated, this)));
    responseList.append(QSharedPointer<LiveDataNode>(new LiveDataNode(QString("Cell Temperature"), getCellTempurature(), common::CELCIUS, m_cellTemperatureSafeRange, &BmsModel::sig_cellTemperatureUpdated, this)));
    responseList.append(QSharedPointer<LiveDataNode>(new LiveDataNode(QString("State of Charge"), getStateOfCharge(), common::PERCENTAGE, m_stateOfChargeSafeRange, &BmsModel::sig_stateOfChargeUpdated, this)));
    responseList.append(QSharedPointer<LiveDataNode>(new LiveDataNode(QString("Buck Temperature"), getBuckTemperature(), common::CELCIUS, m_buckTemperatureSafeRange, &BmsModel::sig_buckTemperatureUpdated, this)));
    responseList.append(QSharedPointer<LiveDataNode>(new LiveDataNode(QString("BMS Current"), getBmsCurrent(), common::AMP, m_bmsCurrentSafeRange, &BmsModel::sig_bmsCurrentUpdated, this)));
    responseList.append(QSharedPointer<LiveDataNode>(new LiveDataNode(QString("MC DC Link Capacitor Voltage"), getMcDcLinkCapacitorVoltage(), common::VOLT, m_mcDcLinkCapacitorVoltageSafeRange, &BmsModel::sig_mcDcLinkCapacitorVoltageUpdated, this)));
    return responseList;
}

///////////////////////////////////////////////////////////////////////////////
///
///                                 PUBLIC SLOTS
///
///////////////////////////////////////////////////////////////////////////////

void BmsModel::slot_bmsBatteryPackCurrentReceived(float batteryPackCurrent)
{
    m_batteryPackCurrent.updateState(batteryPackCurrent);
    emit sig_batteryPackCurrentUpdated(batteryPackCurrent);
}

void BmsModel::slot_bmsBatteryPackVoltageReceived(float batteryPackVoltage)
{
    m_batteryPackVoltage.updateState(batteryPackVoltage);
    emit sig_batteryPackVoltageUpdated(batteryPackVoltage);
}

void BmsModel::slot_bmsCellTemperatureReceived(float cellTemperature)
{
    m_cellTemperature.updateState(cellTemperature);
    emit sig_cellTemperatureUpdated(cellTemperature);
}

void BmsModel::slot_stateOfChargeReveived(float stateOfCharge)
{
    m_stateOfCharge.updateState(stateOfCharge);
    emit sig_stateOfChargeUpdated(stateOfCharge);
}

void BmsModel::slot_buckTemperatureReceived(float buckTemperature)
{
    m_buckTemperature.updateState(buckTemperature);
    emit sig_buckTemperatureUpdated(buckTemperature);
}

void BmsModel::slot_bmsCurrentReceived(float bmsCurrent)
{
    m_bmsCurrent.updateState(bmsCurrent);
    emit sig_bmsCurrentUpdated(bmsCurrent);
}

void BmsModel::slot_mcDcLinkCapacitorReceived(float capacitorVoltage)
{
    m_mcDcLinkCapacitorVoltage.updateState(capacitorVoltage);
    emit sig_mcDcLinkCapacitorVoltageUpdated(capacitorVoltage);
}
