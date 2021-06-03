#ifndef PODCONTROLLER_H
#define PODCONTROLLER_H

#include <QObject>
#include "bmsmodel.h"

class PodController : public QObject
{
    Q_OBJECT
public:
    explicit PodController(QObject *parent = nullptr);

private:
    BmsModel m_bms;
private:


signals:

};

#endif // PODCONTROLLER_H
