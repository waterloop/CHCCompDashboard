#ifndef MOTORCONTROLMODEL_H
#define MOTORCONTROLMODEL_H

#include <QObject>
#include "podstate.h"
#include "livedatamodel/livedatamodelinput.h"
#include "common.h"

using common::OperationalEnvelope;

/*!
 * \brief The MotorControlModel class
 * The Motor Control model class is responsible for storing Up To Date
 * information about the state of the BMS system.
 * Health Check timeouts will be handled by this class and signals
 * will be sent from this class if Motor Control health checks miss their allotted checkins
 */
class MotorControlModel : public QObject, public LiveDataModelInput
{
    Q_OBJECT

public:
    explicit MotorControlModel(QObject* parent=nullptr);

    // getters
//    float getBatteryPackCurrent() const;

    /// LiveDataModelInput Implimentations
    QList<QSharedPointer<LiveDataNode>> enumerate() const override;


private:
    // Values that come from health checks and data dumps
    PodState<QVariant> m_igbtTemperature;
    PodState<QVariant> m_podSpeed;
    PodState<QVariant> m_batteryCurrent;
    PodState<QVariant> m_motorVolage;
    PodState<QVariant> m_batteryVoltage;

    /**
      *  Safe Ranges for the motor control data
      */
    OperationalEnvelope m_igbtTemperatureSafeRange;
    OperationalEnvelope m_podSpeedSafeRange;
    OperationalEnvelope m_batteryCurrentSafeRange;
    OperationalEnvelope m_motorVoltageSafeRange;
    OperationalEnvelope m_batteryVoltageSafeRange;


signals:
    // Signals for when the data is updated
    void sig_igbtTemperatureUpdated(float newIgbtTemperature);
    void sig_podSpeedUpdated(float newPodSpeed);
    void sig_batteryCurerntUpdated(float newBatteryCurrent);
    void sig_motorVoltageUpdated(float newMotorVoltage);
    void sig_bateryVoltageUpdated(float newBatteryVoltage);
    void sig_motorcontrolHealthCheckFailure();

public slots:
    // Slots for when data is received
};

#endif // MOTORCONTROLMODEL_H
