#ifndef PRESSURESENSSORMODEL_H
#define PRESSURESENSSORMODEL_H
#include "podstate.h"
#include "livedatamodel/livedatamodelinput.h"
#include "livedatamodel/livedatanode.h"
#include "QObject"
#include "QString"

/// Pressure Sensors are single valued sensors which only need a Single Pod state to represent their information
/// We alias the type so that the naming convention is kept consistent in the PodController.
class PressureSensorModel : public QObject, public LiveDataModelInput {
    Q_OBJECT
public:
    explicit PressureSensorModel(QString name, float initialPressureValue, OperationalEnvelope maxRange, QObject* parent = nullptr);

    virtual QList<QSharedPointer<LiveDataNode>> enumerate() const;
    float getPressure() const;

    QString getName() const;
private:
    PodState<float> m_pressure;
    OperationalEnvelope m_maxRange;
    QString m_name;

public slots:
    void slot_updatePressure(float pressure);

signals:
    void sig_pressureUpdated(float pressure);
};

//typedef PodState<float> PressureSensorModel;

#endif // PRESSURESENSSORMODEL_H
