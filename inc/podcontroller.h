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
        CURRENT_STATE,
        ERRNO,
        PENDING_NEXT_STATE,
        RECOVERING,
        TELEMETRY,
        TELEMETRY_TIMESTAMP,
        // TELEMETRY FIELDS
        SPEED,
        BATTERY_PACK_VOLTAGE,
        TORCHIC_1,
        TORCHIC_2,
        PRESSURE_HIGH,
        PRESSURE_LOW_1,
        PRESSURE_LOW_2
    };

    QHash<QString, FieldName> m_fieldHash;
signals:
    void sig_currentStateChanged(const PodStates::e_PodState &currentState);
    void sig_requestedStateChanged(const PodStates::e_PodState &requestedState);
    void sig_transitioningChanged();
    void sig_mcDataChanged();
    void sig_torchic1Changed();
    void sig_torchic2Changed();

    void sig_recoveryDetected(); // Disconnect from the pod

    // Telemetry Data signals
    void sig_podSpeedAvailable(const int speed);
    void sig_torchic1DataAvailable(float temp1, float temp2);
    void sig_torchic2DataAvailable(float temp1, float temp2);
};

#endif // PODCONTROLLER_H
