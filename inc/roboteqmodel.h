#ifndef ROBOTEQMODEL_H
#define ROBOTEQMODEL_H
#include <QObject>
#include <podstate.h>
#include "livedatamodel/livedatamodelinput.h"
#include "livedatamodel/livedatanode.h"

class RoboteqModel : public QObject, public LiveDataModelInput {
    Q_OBJECT
    Q_PROPERTY(int speed1 READ getSpeed1 NOTIFY sig_speed1Updated);
    Q_PROPERTY(int speed2 READ getSpeed2 NOTIFY sig_speed2Updated);
    Q_PROPERTY(int temp1 READ getSensor1Temp NOTIFY sig_sensor1TempUpdated);
    Q_PROPERTY(int temp2 READ getSensor2Temp NOTIFY sig_sensor2TempUpdated);
    Q_PROPERTY(int current1 READ getBatteryCurrent1 NOTIFY sig_batteryCurrent1Updated);
    Q_PROPERTY(int current2 READ getBatteryCurrent2 NOTIFY sig_batteryCurrent2Updated);

public:
    explicit RoboteqModel(QObject* parent = nullptr);

    virtual QList<QSharedPointer<LiveDataNode>> enumerate() const;

    int getSpeed1() const;
    int getSpeed2() const;
    int getBatteryCurrent1() const;
    int getBatteryCurrent2() const;
    int getMcuTemp() const;
    int getSensor1Temp() const;
    int getSensor2Temp() const;

private:
    PodState<int> m_speed1;
    PodState<int> m_speed2;
    PodState<int> m_batteryCurrent1;
    PodState<int> m_batteryCurrent2;
    PodState<int> m_mcuTemp;
    PodState<int> m_sensor1Temp;
    PodState<int> m_sensor2Temp;

public slots:
    void slot_speed1Available(int speed);
    void slot_speed2Available(int speed);
    void slot_batteryCurrent1Available(int current);
    void slot_batteryCurrent2Available(int current);
    void slot_mcuTempAvailable(int temp);
    void slot_sensor1TempAvailable(int temp);
    void slot_sensor2TempAvailable(int temp);

signals:
    void sig_speed1Updated(int speed);
    void sig_speed2Updated(int speed);
    void sig_batteryCurrent1Updated(int current);
    void sig_batteryCurrent2Updated(int current);
    void sig_mcuTempUpdated(int temp);
    void sig_sensor1TempUpdated(int temp);
    void sig_sensor2TempUpdated(int temp);

};

#endif // ROBOTEQMODEL_H
