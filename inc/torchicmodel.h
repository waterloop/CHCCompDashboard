#ifndef TORCHICMODEL_H
#define TORCHICMODEL_H
#include <QObject>
#include <QList>
#include <QSharedPointer>
#include <QString>
#include "podstate.h"
#include "livedatamodel/livedatamodelinput.h"
#include "livedatamodel/livedatanode.h"
#include "common.h"

using common::OperationalEnvelope;
/*!
 * @brief The TorchicModel class
 * The Motor Control model class is responsible for storing Up To Date
 * information about the state of torchic board.
 * Health Check timeouts will be handled by this class and signals
 * will be sent from this class if the health checks miss their allotted checkins
 */
class TorchicModel : public QObject, public LiveDataModelInput
{
    Q_OBJECT
    Q_PROPERTY(float temp1 READ getTemperature1 NOTIFY sig_temperatureUpdated)
    Q_PROPERTY(float temp2 READ getTemperature2 NOTIFY sig_temperatureUpdated)
public:
    TorchicModel(QString name, QObject *parent = nullptr);
    virtual ~TorchicModel();

    /// GETTERS
    float getTemperature1() const;
    float getTemperature2() const;

    /// LiveDataModelInput methods
    virtual QList<QSharedPointer<LiveDataNode>> enumerate() const;

public slots:
    void slot_temperaturesAvailable(float temp1, float temp2);

private:
    PodState<float> m_temperature1;
    PodState<float> m_temperature2;

    OperationalEnvelope m_tempurature1SafeRange;
    OperationalEnvelope m_tempurature2SafeRange;

    QString m_name;

signals:
    void sig_temperatureUpdated();
    void sig_temperature1Updated(float);
    void sig_temperature2Updated(float);
};
#endif // TORCHICMODEL_H
