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
    Q_PROPERTY(int podSpeed READ getPodSpeed NOTIFY sig_podSpeedUpdated)

public:
    explicit MotorControlModel(QObject* parent=nullptr);

    /// GETTERS
//    float getBatteryPackCurrent() const;
    float getPodSpeed() const;
    float getBatteryCurrent() const;
    float getIgbtTemperature() const;
    float getMotorVoltage() const;
    float getBatteryVoltage() const;

    /// SETTERS
    void setPodSpeed(const float &podSpeed);


    /// LiveDataModelInput Implimentations
    QList<QSharedPointer<LiveDataNode>> enumerate() const override;

    /// Operator Implementations
    MotorControlModel& operator=(const MotorControlModel& other); // Copy Assignment
    bool operator==(const MotorControlModel& other) const;
    bool operator!=(const MotorControlModel& other) const;


private:
    // Values that come from health checks and data dumps
    PodState<QVariant> m_igbtTemperature;
    PodState<QVariant> m_podSpeed;
    PodState<QVariant> m_batteryCurrent;
    PodState<QVariant> m_motorVoltage;
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
    void slot_podSpeedReceived(float newPodSpeed);
};


#endif // MOTORCONTROLMODEL_H
