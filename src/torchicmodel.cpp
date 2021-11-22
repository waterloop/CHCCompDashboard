# include "torchicmodel.h"

TorchicModel::TorchicModel(QObject *parent)
    : QObject(parent),
      m_temperature1(INTITIAL_TORCHIC_TEMP, TORCHIC_TIMEOUT_MS),
      m_temperature2(INTITIAL_TORCHIC_TEMP, TORCHIC_TIMEOUT_MS)
{

}

TorchicModel::~TorchicModel()
{

}

float TorchicModel::getTemperature1() const
{
    return m_temperature1.getState();
}

void TorchicModel::slot_temperaturesAvailable(float temp1, float temp2)
{
    bool state_changed = temp1 != m_temperature1.getState() || temp2 != m_temperature2.getState();

    this->m_temperature1.updateState(temp1);
    this->m_temperature2.updateState(temp2);

    if (state_changed) {
        emit sig_temperatureUpdated();
    }
}
