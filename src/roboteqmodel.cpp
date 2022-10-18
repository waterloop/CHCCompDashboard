#include "roboteqmodel.h"
#include "common.h"
RoboteqModel::RoboteqModel(QObject* parent)
    : QObject(parent),
      m_speed1(0, 10000, this),
      m_speed2(0, 10000, this),
      m_batteryCurrent1(0, 10000, this),
      m_batteryCurrent2(0, 10000, this),
      m_mcuTemp(0, 10000, this),
      m_sensor1Temp(0, 10000, this),
      m_sensor2Temp(0, 10000, this) {}

///////////////////////////////////////////////////////////////////////////////
///
///                                 PUBLIC ACCESSORS
///
///////////////////////////////////////////////////////////////////////////////
int RoboteqModel::getSpeed1() const {
    return m_speed1.getState();
}
int RoboteqModel::getSpeed2() const {
    return m_speed2.getState();
}
int RoboteqModel::getBatteryCurrent1() const {
    return m_batteryCurrent1.getState();
}
int RoboteqModel::getBatteryCurrent2() const {
    return m_batteryCurrent2.getState();
}
int RoboteqModel::getMcuTemp() const {
    return m_mcuTemp.getState();
}
int RoboteqModel::getSensor1Temp() const {
    return m_sensor1Temp.getState();
}
int RoboteqModel::getSensor2Temp() const {
    return m_sensor2Temp.getState();
}


///////////////////////////////////////////////////////////////////////////////
///
///                                 PUBLIC SLOTS
///
///////////////////////////////////////////////////////////////////////////////
void RoboteqModel::slot_speed1Available(int speed) {
    m_speed1 = speed;
    emit sig_speed1Updated(speed);
}

void RoboteqModel::slot_speed2Available(int speed) {
    m_speed2 = speed;
    emit sig_speed2Updated(speed);
}

void RoboteqModel::slot_batteryCurrent1Available(int current) {
    m_batteryCurrent1 = current;
    emit sig_batteryCurrent1Updated(current);
}

void RoboteqModel::slot_batteryCurrent2Available(int current) {
    m_batteryCurrent2 = current;
    emit sig_batteryCurrent2Updated(current);
}

void RoboteqModel::slot_mcuTempAvailable(int temp) {
    m_mcuTemp = temp;
    emit sig_mcuTempUpdated(temp);
}

void RoboteqModel::slot_sensor1TempAvailable(int temp) {
    m_sensor1Temp = temp;
    emit sig_sensor1TempUpdated(temp);
}

void RoboteqModel::slot_sensor2TempAvailable(int temp) {
    m_sensor2Temp = temp;
    emit sig_sensor2TempUpdated(temp);
}

///////////////////////////////////////////////////////////////////////////////
///
///                    Public LiveDataModelInput Methods
///
///////////////////////////////////////////////////////////////////////////////
QList<QSharedPointer<LiveDataNode>> RoboteqModel::enumerate() const
{
    QList<QSharedPointer<LiveDataNode>> responseList;
//    new LiveDataNode(
//                QString("Torchic Tempurature 1"),
//                getTemperature1(),
//                common::CELCIUS,
//                m_tempurature1SafeRange,
//                &TorchicModel::sig_temperatureUpdated,
//                this);
    responseList.append(QSharedPointer<LiveDataNode>(new LiveDataNode(QString("roboteq Speed 1"), QVariant(getSpeed1()), common::UNDEFINED, OperationalEnvelope{ .max= 1000, .min=0}, &RoboteqModel::sig_speed1Updated, this)));
    responseList.append(QSharedPointer<LiveDataNode>(new LiveDataNode(QString("roboteq Speed 2"), QVariant(getSpeed2()), common::UNDEFINED, OperationalEnvelope{ .max= 1000, .min=0}, &RoboteqModel::sig_speed2Updated, this)));
    responseList.append(QSharedPointer<LiveDataNode>(new LiveDataNode(QString("MCU TEMP"), QVariant(getMcuTemp()), common::UNDEFINED, OperationalEnvelope{ .max= 1000, .min=0}, &RoboteqModel::sig_mcuTempUpdated, this)));
    responseList.append(QSharedPointer<LiveDataNode>(new LiveDataNode(QString("RT sense temp 1"), QVariant(getSensor1Temp()), common::UNDEFINED, OperationalEnvelope{ .max= 1000, .min=0}, &RoboteqModel::sig_sensor1TempUpdated, this)));
    responseList.append(QSharedPointer<LiveDataNode>(new LiveDataNode(QString("RT sense temp 2"), QVariant(getSensor2Temp()), common::UNDEFINED, OperationalEnvelope{ .max= 1000, .min=0}, &RoboteqModel::sig_sensor2TempUpdated, this)));
    responseList.append(QSharedPointer<LiveDataNode>(new LiveDataNode(QString("roboteq Bat current 1"), QVariant(getBatteryCurrent1()), common::UNDEFINED, OperationalEnvelope{ .max= 1000, .min=0}, &RoboteqModel::sig_batteryCurrent1Updated, this)));
    responseList.append(QSharedPointer<LiveDataNode>(new LiveDataNode(QString("roboteq Bat Current 2"), QVariant(getBatteryCurrent2()), common::UNDEFINED, OperationalEnvelope{ .max= 1000, .min=0}, &RoboteqModel::sig_batteryCurrent2Updated, this)));

//    responseList.append(QSharedPointer<LiveDataNode>(new LiveDataNode(QString("Battery Pack Voltage"), getBatteryPackVoltage(), common::VOLT, m_batterPackVoltageSafeRange, &BmsModel::sig_batteryPackVoltageUpdated, this)));
//    responseList.append(QSharedPointer<LiveDataNode>(new LiveDataNode(QString("Cell Temperature"), getCellTempurature(), common::CELCIUS, m_cellTemperatureSafeRange, &BmsModel::sig_cellTemperatureUpdated, this)));
//    responseList.append(QSharedPointer<LiveDataNode>(new LiveDataNode(QString("State of Charge"), getStateOfCharge(), common::PERCENTAGE, m_stateOfChargeSafeRange, &BmsModel::sig_stateOfChargeUpdated, this)));
//    responseList.append(QSharedPointer<LiveDataNode>(new LiveDataNode(QString("Buck Temperature"), getBuckTemperature(), common::CELCIUS, m_buckTemperatureSafeRange, &BmsModel::sig_buckTemperatureUpdated, this)));
//    responseList.append(QSharedPointer<LiveDataNode>(new LiveDataNode(QString("BMS Current"), getBmsCurrent(), common::AMP, m_bmsCurrentSafeRange, &BmsModel::sig_bmsCurrentUpdated, this)));
//    responseList.append(QSharedPointer<LiveDataNode>(new LiveDataNode(QString("MC DC Link Capacitor Voltage"), getMcDcLinkCapacitorVoltage(), common::VOLT, m_mcDcLinkCapacitorVoltageSafeRange, &BmsModel::sig_mcDcLinkCapacitorVoltageUpdated, this)));
    return responseList;
}

