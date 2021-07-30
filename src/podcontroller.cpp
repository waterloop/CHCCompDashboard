#include "inc/podcontroller.h"

PodController::PodController(QObject *parent) : QObject(parent),
    m_bmsData(this),
    m_liveData(this)
{
    m_liveData.insertData(m_bmsData);
}

LiveDataModel* PodController::getLiveData()
{
    return &m_liveData;
}
