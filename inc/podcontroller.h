#ifndef PODCONTROLLER_H
#define PODCONTROLLER_H

#include <QObject>
#include "bmsmodel.h"
#include "livedatamodel/livedatamodel.h"

class PodController : public QObject
{
    Q_OBJECT
public:
    explicit PodController(QObject *parent = nullptr);

    LiveDataModel* getLiveData();

private:
    BmsModel m_bmsData;
    LiveDataModel m_liveData;

signals:

};

#endif // PODCONTROLLER_H
