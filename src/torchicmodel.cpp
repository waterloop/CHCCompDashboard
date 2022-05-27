# include "torchicmodel.h"

TorchicModel::TorchicModel(QObject *parent)
    : QObject(parent),
      m_temperature1(INTITIAL_TORCHIC_TEMP, TORCHIC_TIMEOUT_MS),
      m_temperature2(INTITIAL_TORCHIC_TEMP, TORCHIC_TIMEOUT_MS),
      m_tempurature1SafeRange({ .max= TORCHIC_MAX_TEMP, .min=TORCHIC_MIN_TEMP }),
      m_tempurature2SafeRange({ .max= TORCHIC_MAX_TEMP, .min=TORCHIC_MIN_TEMP })
{
    connect(this, &TorchicModel::sig_temperature1Updated,
            this, &TorchicModel::sig_temperatureUpdated);
    connect(this, &TorchicModel::sig_temperature2Updated,
            this, &TorchicModel::sig_temperatureUpdated);
}

TorchicModel::~TorchicModel()
{

}

///////////////////////////////////////////////////////////////////////////////
///
///                                 PUBLIC ACCESSORS
///
///////////////////////////////////////////////////////////////////////////////

float TorchicModel::getTemperature1() const
{
    return m_temperature1.getState();
}

float TorchicModel::getTemperature2() const
{
    return m_temperature2.getState();
}

///////////////////////////////////////////////////////////////////////////////
///
///                                 PUBLIC SLOTS
///
///////////////////////////////////////////////////////////////////////////////

void TorchicModel::slot_temperaturesAvailable(float temp1, float temp2)
{
    bool state_changed = temp1 != m_temperature1.getState() || temp2 != m_temperature2.getState();

    this->m_temperature1.updateState(temp1);
    this->m_temperature2.updateState(temp2);

    if (state_changed) {
        qDebug() << "TORCHIC TEMP UPDATED";
        emit sig_temperatureUpdated();
        emit sig_temperature1Updated(temp1);
        emit sig_temperature2Updated(temp2);
    }
}
///////////////////////////////////////////////////////////////////////////////
///
///                    Public LiveDataModelInput Methods
///
///////////////////////////////////////////////////////////////////////////////
QList<QSharedPointer<LiveDataNode>> TorchicModel::enumerate() const
{
    QList<QSharedPointer<LiveDataNode>> responseList;
//    new LiveDataNode(
//                QString("Torchic Tempurature 1"),
//                getTemperature1(),
//                common::CELCIUS,
//                m_tempurature1SafeRange,
//                &TorchicModel::sig_temperatureUpdated,
//                this);
    responseList.append(QSharedPointer<LiveDataNode>(new LiveDataNode(QString("Temperature Data 1"), getTemperature1(), common::CELCIUS, m_tempurature1SafeRange, &TorchicModel::sig_temperature1Updated, this)));
    responseList.append(QSharedPointer<LiveDataNode>(new LiveDataNode(QString("Temperature Data 2"), getTemperature2(), common::CELCIUS, m_tempurature2SafeRange, &TorchicModel::sig_temperature2Updated, this)));

//    responseList.append(QSharedPointer<LiveDataNode>(new LiveDataNode(QString("Battery Pack Voltage"), getBatteryPackVoltage(), common::VOLT, m_batterPackVoltageSafeRange, &BmsModel::sig_batteryPackVoltageUpdated, this)));
//    responseList.append(QSharedPointer<LiveDataNode>(new LiveDataNode(QString("Cell Temperature"), getCellTempurature(), common::CELCIUS, m_cellTemperatureSafeRange, &BmsModel::sig_cellTemperatureUpdated, this)));
//    responseList.append(QSharedPointer<LiveDataNode>(new LiveDataNode(QString("State of Charge"), getStateOfCharge(), common::PERCENTAGE, m_stateOfChargeSafeRange, &BmsModel::sig_stateOfChargeUpdated, this)));
//    responseList.append(QSharedPointer<LiveDataNode>(new LiveDataNode(QString("Buck Temperature"), getBuckTemperature(), common::CELCIUS, m_buckTemperatureSafeRange, &BmsModel::sig_buckTemperatureUpdated, this)));
//    responseList.append(QSharedPointer<LiveDataNode>(new LiveDataNode(QString("BMS Current"), getBmsCurrent(), common::AMP, m_bmsCurrentSafeRange, &BmsModel::sig_bmsCurrentUpdated, this)));
//    responseList.append(QSharedPointer<LiveDataNode>(new LiveDataNode(QString("MC DC Link Capacitor Voltage"), getMcDcLinkCapacitorVoltage(), common::VOLT, m_mcDcLinkCapacitorVoltageSafeRange, &BmsModel::sig_mcDcLinkCapacitorVoltageUpdated, this)));
    return responseList;
}

