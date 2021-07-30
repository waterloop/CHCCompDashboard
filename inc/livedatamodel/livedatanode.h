#ifndef LIVEDATANODE_H
#define LIVEDATANODE_H

#include <QString>
#include <QVariant>
#include <QObject>
#include <QPointer>
#include <QVariant>
#include "common.h"
#include "podstate.h"
using common::OperationalEnvelope;
///
/// \brief The LiveDataNode class
/// The LiveDataNode class holds a
/// single data point for the live data
/// model. It is populated via the Pod's
/// system models and then passed to the
/// live data model
///
class LiveDataNode : public QObject {
    Q_OBJECT
public:
    template<typename T>
    explicit LiveDataNode(QString name, QVariant data, common::Unit unit, OperationalEnvelope safeRange, void (T::*)(float), const T* signalCaller, QObject *parent=nullptr);

    QString name;
    QVariant data;
    common::Unit unit;
    OperationalEnvelope safeRange;

public slots:
    void slot_updateData(QVariant newData);

signals:
    void sig_dataUpdated();
};

template <typename T>
LiveDataNode::LiveDataNode(QString name, QVariant data, common::Unit unit, OperationalEnvelope safeRange, void (T::*signal)(float), const T* signalCaller, QObject *parent)
    : QObject(parent),
      name(name),
      data(data),
      unit(unit),
      safeRange(safeRange)
{
    connect(signalCaller, signal, this, &LiveDataNode::slot_updateData);
}

#endif // LIVEDATANODE_H
