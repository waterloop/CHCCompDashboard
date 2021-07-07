#ifndef COMMON_H
#define COMMON_H
#include <Qt>


/**********************
 * Common Definitions *
 *********************/

#define RELAY_BOARD_HANDSHAKE_REQUEST "HANDSHAKE\r\nDESKTOP\r\n"
#define RELAY_BOARD_MOCK_CAN_REQUEST "SEND MOCK CAN\r\n"
#define RELAY_BOARD_DEFAULT_TCP_PORT 8080
#define DEV_HOST "127.0.0.1"

/******************************
 * Singletons for Controllers *
 *****************************/

/* Singleton Pod Object which manages
 * the state of the pod via various models
 */
class PodController;
extern PodController *pod;

/*
 * Network Interface Layer
 * Handles all external communication
 */
class NetworkController;
extern NetworkController *network_controller;

/********************
 * Type Definitions *
 *******************/

typedef quint16 port_t;

#endif
