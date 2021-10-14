#include "inc/podcontroller.h"
#include <QDebug>

PodController::PodController(QObject *parent) : QObject(parent),
    m_bmsData(this),
    m_liveData(this),
    m_currentAction(Action::STOP)
{
    m_liveData.insertData(m_bmsData);
}

LiveDataModel* PodController::getLiveData()
{
    return &m_liveData;
}

Action PodController::getCurrentAction() const
{
    return m_currentAction;
}

void PodController::setCurrentAction(const Action &currentAction)
{
    qDebug() << "Setting Current Action to " << currentAction;
    m_currentAction = currentAction;
}
