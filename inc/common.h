#ifndef COMMON_H
#define COMMON_H
#include <Qt>
#include <QVariant>
#include <QtQml>

/**********************
 * Common Definitions *
 **********************/

#define RELAY_BOARD_HANDSHAKE_REQUEST "CONNECT\r\n"
#define RELAY_BOARD_DISCONNECT "DISCONNECT\r\n"
#define RELAY_BOARD_MOCK_CAN_REQUEST "SEND MOCK CAN\r\n"
#define RELAY_BOARD_DEFAULT_PORT 8080
#define DEV_HOST "127.0.0.1" // loopback
//#define DEV_HOST "192.168.1.141" // Pi from the context of Waterloop Router
//#define DEV_HOST "129.97.181.138" // was the pi at one point
//#define DEV_HOST "raspberrypi.local"

/*********************
 *   BMS CONSTANTS   *
 *********************/
#define INITIAL_BATPACK_CURRENT -1.0f
#define BATPACK_CURRENT_TIMEOUT_MS (1000*7) // 7 seconds
#define BATPACK_MAX_CURRENT 100 // TODO: CHANGE ME
#define BATPACK_MIN_CURRENT 0   // TODO: CHANGE ME

#define INITIAL_BATPACK_VOLTAGE -1.0f
#define BATPACK_VOLTAGE_TIMEOUT_MS (1000*7) // 7 seconds
#define BATPACK_MAX_VOLTAGE  100 // TODO: CHANGE ME
#define BATPACK_MIN_VOLTAGE 0   // TODO: CHANGE ME

#define INITIAL_CELL_TEMP -1.0f
#define CELL_TEMP_TIMEOUT_MS (1000*7) // 7 seconds
#define CELL_MAX_TEMP 100 // TODO: CHANGE ME
#define CELL_MIN_TEMP 0   // TODO: CHANGE ME

#define INITIAL_STATE_OF_CHARGE -1.0f
#define STATE_OF_CHARGE_TIMEOUT_MS (1000*7) // 7 seconds
#define STATE_OF_CHARGE_MAX 100 // TODO: CHANGE ME
#define STATE_OF_CHARGE_MIN 0   // TODO: CHANGE ME


#define INITIAL_BUCK_TEMP -1.0f
#define BUCK_TEMP_TIMEOUT_MS (1000*7) // 7 seconds
#define BUCK_MAX_TEMP 100 // TODO: CHANGE ME
#define BUCK_MIN_TEMP 0   // TODO: CHANGE ME

#define INITIAL_BMS_CURRENT -1.0f
#define BMS_CURRENT_TIMEOUT_MS (1000*7) // 7 seconds
#define BMS_MAX_CURRENT 100 // TODO: CHANGE ME
#define BMS_MIN_CURRENT 0   // TODO: CHANGE ME

#define INITIAL_DC_LINK_CAP_VOLTAGE -1.0f
#define DC_LINK_CAP_VOLTAGE_TIMEOUT_MS (1000*7) // 7 seconds
#define DC_LINK_CAP_MAX_VOLTAGE 100 // TODO: CHANGE ME
#define DC_LINK_CAP_MIN_VOLTAGE 0   // TODO: CHANGE ME

/**********************************
 *   Motor Controller CONSTANTS   *
 **********************************/
#define INITIAL_POD_SPEED 0.0f
#define POD_SPEED_TIMEOUT_MS (1000*7) // 7 seconds
#define POD_SPEED_MAX 1000000 // TODO: CHANGE ME
#define POD_SPEED_MIN 0       // TODO: CHANGE ME

#define INITIAL_IGBT_TEMP 0.0f
#define IGBT_TEMP_TIMEOUT_MS (1000*7) // 7 seconds
#define IGBT_MAX_TEMP 200
#define IGBT_MIN_TEMP 0

#define INITIAL_BATTERY_CURRRENT 0.0f
#define BATTERY_CURRENT_TIMEOUT_MS (1000*7) // 7 seconds
#define BATTERY_MAX_CURRENT 100 // TODO: CHANGE ME
#define BATTERY_MIN_CURRENT 0   // TODO: CHANGE ME

#define INITIAL_MOTOR_VOLTAGE 0.0f
#define MOTOR_VOLTAGE_TIMEOUT_MS (1000*7) // 7 seconds
#define MOTOR_MAX_VOLTAGE 100 // TODO: CHANGE ME
#define MOTOR_MIN_VOLTAGE 0   // TODO: CHANGE ME

#define INITIAL_BATTERY_VOLTAGE 0.0f
#define BATTERY_VOLTAGE_TIMEOUT_MS (1000*7) // 7 seconds
#define BATTERY_MAX_VOLTAGE 100 // TODO: CHANGE ME
#define BATTERY_MIN_VOLTAGE 0   // TODO: CHANGE ME

/*************************
 *   Torchic CONSTANTS   *
 *************************/
#define INTITIAL_TORCHIC_TEMP 32.0f // celcius
#define TORCHIC_TIMEOUT_MS (1000*7) // 7 seconds
#define TORCHIC_MAX_TEMP 200        // celcius
#define TORCHIC_MIN_TEMP 0          // celcius

/*********************************
 *   Pressure Sensor CONSTANTS   *
 *********************************/
#define INITIAL_PRESSURE_HIGH 100   // psi?
#define INITIAL_PRESSURE_LOW 3      // psi?
#define PRESURE_TIMEOUT_MS (1000*7) // seconds

/******************************
 * Singletons for Controllers *
 ******************************/

/* Singleton Pod Object which manages
 * the state of the pod via various models
 */
class PodController;
extern PodController *pod;

/* Singlton Network Interface Controller
 * Handles all external communication
 */
class NetworkController;
extern NetworkController *network_controller;

// The common Namespace for common type and enum definitions
namespace common {
Q_NAMESPACE
    /********************
     * Type Definitions *
     *******************/

    typedef quint16 port_t;
    typedef int Millisecond;

    /********************
     * Enum Definitions *
     *******************/
    enum Unit {
        UNDEFINED, // aka unitless quantities
        VOLT,
        AMP,
        PERCENTAGE,
        CELCIUS
    };
     Q_ENUM_NS(Unit)


    /**********************
     * Struct Definitions *
     **********************/
    ///
    /// In the context of our pod, the operational
    /// evelope is a range of values which corispond
    /// to a state of operation.
    /// These ranges generally corespond to the following ranges:
    ///     Safe
    ///     Warning
    ///     Error
    /// --------------
    /// Each of the these ranges can be represented by an
    /// operational envelope
    ///
    typedef struct operational_envelope{
        QVariant max;
        QVariant min;
    } OperationalEnvelope;

    /*************************
     * Function declarations *
     *************************/
//    e_PodState from_int(int value);
}

/*************************
 * QML TYPE DECLARATIONS *
 *************************/
///
/// QML Types must be declared at a global level so they are declared here
/// rather then inside of the common namespace
///
//QML_DECLARE_TYPE(common::e_PodState)

class PodStates : public QObject {
    Q_OBJECT
public:
    /**
     * @brief The e_PodState enum
     * Enumerated Versions of our Pod's states.
     * We needed to overload the name because we use
     * PodState to define a Class that handles Telemetry.
     * Might Refactor that later to call it PodData instead,
     * but until then we'll stick with this.
     */
    enum e_PodState {
        Resting                 = 0,
        LowVoltage             = 1,
        Armed                   = 2,
        AutoPilot               = 3,
        Braking                 = 4,
        EmergencyBrake          = 5,
        SystemFailure           = 6,
        ManualOperationWaiting  = 7,
        Accellerating           = 8,
        AtSpeed                 = 9,
        Decelerating            = 10,
        Invalid                 = 11,
    };
    Q_ENUM(e_PodState)

    inline static PodStates::e_PodState from_int(int val);
};

inline PodStates::e_PodState PodStates::from_int(int val)
{
    switch (val) {
    case 0:
        return e_PodState::Resting;
    case 1:
        return e_PodState::LowVoltage;
    case 2:
        return e_PodState::Armed;
    case 3:
        return e_PodState::AutoPilot;
    case 4:
        return e_PodState::Braking;
    case 5:
        return e_PodState::EmergencyBrake;
    case 6:
        return e_PodState::SystemFailure;
    case 7:
        return e_PodState::ManualOperationWaiting;
    case 8:
        return e_PodState::Accellerating;
    case 9:
        return e_PodState::AtSpeed;
    case 10:
        return e_PodState::Decelerating;
    default:
        return e_PodState::Invalid;
    }
}


#endif
