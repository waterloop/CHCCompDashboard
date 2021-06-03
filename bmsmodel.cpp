#include "bmsmodel.h"

BmsModel::BmsModel(QObject* parent)
    : QObject(parent),
      m_batteryPackCurrent(INITIAL_BATPACK_CURRENT, BATPACK_CURRENT_TIMEOUT_MS, this),
      m_cellTempurature(INITIAL_CELL_TEMP, CELL_TEMP_TIMEOUT_MS, this)
{
    connect(&m_batteryPackCurrent, &PodState<float>::sig_stateHealthCheckMissed, this, &BmsModel::sig_bmsHealthCheckFailure);
    connect(&m_cellTempurature, &PodState<float>::sig_stateHealthCheckMissed, this, &BmsModel::sig_bmsHealthCheckFailure);
}


void BmsModel::slot_bmsBatteryPackCurrentReceived(float batteryPackCurrent)
{
    m_batteryPackCurrent.updateState(batteryPackCurrent);
    emit sig_batteryPackCurrentUpdated();
}

void BmsModel::slot_bmsCellTempuratureReceived(float cellTempurature)
{
    m_cellTempurature.updateState(cellTempurature);
    emit sig_batteryPackCurrentUpdated();
}

float BmsModel::getBatteryPackCurrent()
{
    return m_batteryPackCurrent.getState();
}

float BmsModel::getCellTempurature()
{
    return m_cellTempurature.getState();
}
