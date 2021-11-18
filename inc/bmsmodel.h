#ifndef BMSMODEL_H
#define BMSMODEL_H

#include <QObject>
#include "podstate.h"
#include "livedatamodel/livedatamodelinput.h"
#include "common.h"

using common::OperationalEnvelope;

/*!
 * \brief The BMSmodel class
 * The BMS model class is responsible for storing Up To Date
 * information about the state of the BMS system.
 * Health Check timeouts will be handled by this class and signals
 * will be sent from this class if BMS health checks miss their allotted checkins
 */
class BmsModel : public QObject, public LiveDataModelInput
{
    Q_OBJECT

public:
    explicit BmsModel(QObject* parent=nullptr);

    float getBatteryPackCurrent() const;
    float getBatteryPackVoltage() const;
    float getCellTempurature() const;
    float getStateOfCharge() const;
    float getBuckTemperature() const;
    float getBmsCurrent() const;
    float getMcDcLinkCapacitorVoltage() const;

    /// LiveDataModelInput Implimentations
    QList<QSharedPointer<LiveDataNode>> enumerate() const override;


private:
    // Values that come from health checks and data dumps
    PodState<QVariant> m_batteryPackCurrent;
    PodState<QVariant> m_batteryPackVoltage;
    PodState<QVariant> m_cellTemperature;
    PodState<QVariant> m_stateOfCharge;
    PodState<QVariant> m_buckTemperature;
    PodState<QVariant> m_bmsCurrent;
    PodState<QVariant> m_mcDcLinkCapacitorVoltage;

    /**
      *  Safe Ranges for the BMS data
      */
    OperationalEnvelope m_batterPackCurrentSafeRange;
    OperationalEnvelope m_batterPackVoltageSafeRange;
    OperationalEnvelope m_cellTemperatureSafeRange;
    OperationalEnvelope m_stateOfChargeSafeRange;
    OperationalEnvelope m_buckTemperatureSafeRange;
    OperationalEnvelope m_bmsCurrentSafeRange;
    OperationalEnvelope m_mcDcLinkCapacitorVoltageSafeRange;


signals:
    void sig_batteryPackCurrentUpdated(float batteryPackCurrent);
    void sig_batteryPackVoltageUpdated(float batteryPackVoltage);
    void sig_cellTemperatureUpdated(float cellTempurature);
    void sig_stateOfChargeUpdated(float stateOfCharge);
    void sig_buckTemperatureUpdated(float buckTemperature);
    void sig_bmsCurrentUpdated(float bmsCurrent);
    void sig_mcDcLinkCapacitorVoltageUpdated(float capacitorVoltage);
    void sig_bmsHealthCheckFailure();

public slots:
    void slot_bmsBatteryPackCurrentReceived(float batteryPackCurrent);
    void slot_bmsBatteryPackVoltageReceived(float batteryPackVoltage);
    void slot_bmsCellTemperatureReceived(float cellTempurature);
    void slot_stateOfChargeReveived(float stateOfCharge);
    void slot_buckTemperatureReceived(float buckTemperature);
    void slot_bmsCurrentReceived(float bmsCurrent);
    void slot_mcDcLinkCapacitorReceived(float capacitorVoltage);
};

#endif // BMSMODEL_H
