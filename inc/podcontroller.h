#ifndef PODCONTROLLER_H
#define PODCONTROLLER_H

#include <QObject>
#include "bmsmodel.h"
#include "livedatamodel/livedatamodel.h"
#include "common.h"

using common::Action;

class PodController : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(Action currentAction READ getCurrentAction WRITE setCurrentAction NOTIFY sig_currentActionChanged)
    explicit PodController(QObject *parent = nullptr);

    LiveDataModel* getLiveData();

    Action getCurrentAction() const;
    void setCurrentAction(const Action &currentAction);

private:
    BmsModel m_bmsData;         // Stores Data relavent to the bms system
    LiveDataModel m_liveData;   // QML friendly model which provides a list of up to date information from various pod systems

    Action m_currentAction;
signals:
    void sig_currentActionChanged(const Action &currentAction);
};

#endif // PODCONTROLLER_H
