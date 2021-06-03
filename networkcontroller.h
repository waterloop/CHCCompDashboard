#ifndef NETWORKCONTROLLER_H
#define NETWORKCONTROLLER_H
#include <QObject>

/*!
 * \brief The NetworkController class
 * The NetworkController is responsible for communicating with
 * the relay board over the network and emiting signals when messages are received
 */
class NetworkController : public QObject
{
    Q_OBJECT
public:
    NetworkController(QObject* parent = nullptr);
};

#endif // NETWORKCONTROLLER_H
