#ifndef COMMON_H
#define COMMON_H
#include <Qt>
#include <QVariant>
#include <QtQml>

/**********************
 * Common Definitions *
 **********************/

#define RELAY_BOARD_HANDSHAKE_REQUEST "HANDSHAKE\r\nDESKTOP\r\n"
#define RELAY_BOARD_MOCK_CAN_REQUEST "SEND MOCK CAN\r\n"
#define RELAY_BOARD_DEFAULT_TCP_PORT 8080
//#define DEV_HOST "127.0.0.1"
#define DEV_HOST "129.97.181.138"

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


/******************************
 * Singletons for Controllers *
 ******************************/

/* Singleton Pod Object which manages
 * the state of the pod via various models
 */
class PodController;
extern PodController *pod;

/*
 * Singlton Network Interface Controller
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

    // Current Messsage that the pod is sending to the relay board.
    // Using an enum for now. May need to upgrade in the future
    enum Action {
        GO,
        STOP,
    };
    Q_ENUM_NS(Action)

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
}

/*************************
 * QML TYPE DECLARATIONS *
 *************************/
///
/// QML Types must be declared at a global level so they are declared here
/// rather then inside of the common namespace
///
QML_DECLARE_TYPE(common::Action)

#endif
