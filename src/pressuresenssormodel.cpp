#include "pressuresenssormodel.h"

PressureSensorModel::PressureSensorModel(QString name, float initialPressureValue, OperationalEnvelope maxRange, QObject* parent)
    : QObject(parent),
      m_pressure(initialPressureValue, PRESURE_TIMEOUT_MS, this),
      m_maxRange(maxRange),
      m_name(name)
{}


///////////////////////////////////////////////////////////////////////////////
///
///                                 PUBLIC ACCESSORS
///
///////////////////////////////////////////////////////////////////////////////
float PressureSensorModel::getPressure() const {
    return m_pressure.getState();
}

QString PressureSensorModel::getName() const {
    return m_name;
}

///////////////////////////////////////////////////////////////////////////////
///
///                                 PUBLIC SLOTS
///
///////////////////////////////////////////////////////////////////////////////
void PressureSensorModel::slot_updatePressure(float pressure) {
    if (getPressure() != pressure) {
        m_pressure = pressure;
        emit sig_pressureUpdated(pressure);
    }
}

///////////////////////////////////////////////////////////////////////////////
///
///                    Public LiveDataModelInput Methods
///
///////////////////////////////////////////////////////////////////////////////
QList<QSharedPointer<LiveDataNode>> PressureSensorModel::enumerate() const {
    QList<QSharedPointer<LiveDataNode>> responseList;
    responseList.append(QSharedPointer<LiveDataNode>(new LiveDataNode(getName(), getPressure(), common::UNDEFINED, m_maxRange, &PressureSensorModel::sig_pressureUpdated, this)));
    return responseList;
}
