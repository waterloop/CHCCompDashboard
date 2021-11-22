#ifndef PRESSURESENSSORMODEL_H
#define PRESSURESENSSORMODEL_H
#include "podstate.h"

/// Pressure Sensors are single valued sensors which only need a Single Pod state to represent their information
/// We alias the type so that the naming convention is kept consistent in the PodController.
typedef PodState<float> PressureSensorModel;

#endif // PRESSURESENSSORMODEL_H
