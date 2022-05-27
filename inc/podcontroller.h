#ifndef PODCONTROLLER_H
#define PODCONTROLLER_H

#include <QObject>
#include "bmsmodel.h"
#include "motorcontrolmodel.h"
#include "torchicmodel.h"
#include "livedatamodel/livedatamodel.h"
#include "common.h"
#include "pressuresenssormodel.h"

class PodController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(PodStates::e_PodState currentState READ getCurrentState NOTIFY sig_currentStateChanged)
    Q_PROPERTY(PodStates::e_PodState requestedState READ getRequestedState WRITE setRequestedState NOTIFY sig_requestedStateChanged)
    Q_PROPERTY(bool transistioning READ isTransitioning NOTIFY sig_transitioningChanged)
    Q_PROPERTY(MotorControlModel* motorController MEMBER m_mcData NOTIFY sig_mcDataChanged)
    Q_PROPERTY(TorchicModel* torchic1 MEMBER m_torchic1 NOTIFY sig_torchic1Changed)
    Q_PROPERTY(TorchicModel* torchic2 MEMBER m_torchic2 NOTIFY sig_torchic2Changed)

public:
    explicit PodController(QObject *parent = nullptr);
    ~PodController();

    LiveDataModel* getLiveData();

    bool isTransitioning() const;
    bool setTransitioning(bool newState);

    PodStates::e_PodState getCurrentState() const;
    PodStates::e_PodState getRequestedState() const;

    void setCurrentState(const PodStates::e_PodState &currentState);
    void setRequestedState(const PodStates::e_PodState &requestedState);
public slots:
    void slot_handlePodMessage(QJsonObject podMessage); // Connects to the UDP Conntroller

private:
    BmsModel* m_bmsData;                    // Stores Data relavent to the bms system
    MotorControlModel* m_mcData;            // Stores Data relavent to the mc system
    TorchicModel* m_torchic1;               // Stores Data from Torchic 1
    TorchicModel* m_torchic2;                // Stores Data from Torchic 2
    PressureSensorModel* m_pressureHigh;    // Stores Data for the High Pressure Sensor
    PressureSensorModel* m_pressureLow1;    // Stores Data for the first Low Pressure Sensor
    PressureSensorModel* m_pressureLow2;    // Stores Data for the second Low Pressure Sensor

    LiveDataModel m_liveData;   // QML friendly model which provides a list of up to date information from various pod systems

    PodStates::e_PodState m_currentState;
    PodStates::e_PodState m_requestedState;

    /**
     * @brief The FieldName enum
     * FieldName is a mapping from any key that can occur in a podMessage, reguardless of the structure of the data structure
     * Paired with the fieldHash, it will allow us to parse and handle the keys from the podMessages
     */
    enum FieldName {

        // TELEMETRY FIELDS
        BATTERY_PACK_CURRENT = 1, //aligns with lookup table in the tsdb
        AVERAGE_CELL_TEMPERATURE,
        IGBT_TEMPERATURE,
        MOTOR_VOLTAGE,
        BATTERY_PACK_VOLTAGE,
        BUCK_TEMPERATURE,
        BMS_CURRENT,
        LINK_CAP_VOLTAGE,
        MOTOR_CURRENT,
        BATTERY_CURRENT,
        BATTERY_VOLTAGE,
        SPEED,
        TORCHIC_1,
        TORCHIC_2,
        PRESSURE_HIGH,
        PRESSURE_LOW_1,
        PRESSURE_LOW_2,
        STATE_OF_CHARGE,
        // OTHER FIELDS
        CURRENT_STATE,
        ERRNO,
        PENDING_NEXT_STATE,
        RECOVERING,
        TELEMETRY,
        TELEMETRY_TIMESTAMP
    };

    QHash<QString, FieldName> m_fieldHash;
signals:
    void sig_currentStateChanged(const PodStates::e_PodState &currentState);
    void sig_requestedStateChanged(const PodStates::e_PodState &requestedState);
    void sig_transitioningChanged();
    void sig_mcDataChanged();
    void sig_torchic1Changed();
    void sig_torchic2Changed();
    void sig_pressureHighChanged();
    void sig_pressureLow1Changed();
    void sig_pressureLow2Changed();

    void sig_recoveryDetected(); // Disconnect from the pod

    // Telemetry Data signals
    void sig_podSpeedAvailable(const int speed);
    void sig_torchic1DataAvailable(float temp1, float temp2);
    void sig_torchic2DataAvailable(float temp1, float temp2);
    void sig_batteryPackCurrentAvailable(float current);
    void sig_batteryPackVoltageAvailable(float voltage);
    void sig_averageCellTemperatureAvailable(float temp);
    void sig_igbtTempAvailable(float temp);
    void sig_motorVoltageAvailable(float motorVoltage);
    void sig_buckTemperatureAvailable(float temp);
    void sig_bmsCurrentAvailable(float amps);
    void sig_linkCapVoltageAvailable(float voltage);
    void sig_motorCurrentAvailable(float current);
    void sig_batteryCurrentAvailable(float current);
    void sig_batteryVoltageAvailable(float votlage);
    void sig_pressureHighDataAvailable(float pressure);
    void sig_pressureLow1DataAvailable(float pressure);
    void sig_pressureLow2DataAvailable(float pressure);
    void sig_stateOfChargeAvailable(float percent);
};

#endif // PODCONTROLLER_H
