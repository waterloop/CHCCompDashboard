#ifndef PODSTATE_H
#define PODSTATE_H

#include <QObject>
#include <QTimer>
#include "common.h"

using common::Unit;
using common::Millisecond;

/*!
 * \brief The AbstractPodState class
 * This is an intermidiary class which will allow the PodState class to use both templates
 * and signals and slots. The signals and slots need to be defined here, then the rest of
 * the class will be defined in the PodState class
 */
class AbstractPodState : public QObject {
    Q_OBJECT
public:
    explicit AbstractPodState(QObject *parent = nullptr): QObject(parent) {}


protected:
    // To impliment the slot in the template child class
    // simply define this function and it will get called when
    // the slot is triggered
    virtual void startStateHealthWatcher() = 0;

public slots:
    void slot_startStateHealthWatcher() {
        startStateHealthWatcher();
    };

signals:
    /* signal which is emited when data has not been received in time */
    void sig_stateHealthCheckMissed();

};

/*!
 * \brief The PodState class
 * PodState manages a piece of data from the pod
 * This includes storing the value of the data and notifying
 * it's parent if that data has not been updated in time.
 * The class is templated to be able to store any type of datum (float, int, etc)
 */
template <typename T>
class PodState : public AbstractPodState
{
public:
    explicit PodState(T initialValue, Millisecond stateHealthTimeout, QObject *parent = nullptr);

    void updateState(T newState);
    T getState() const;
    void slot_startStateHealthWatcher();

    /// Copy Assignment
    /// Allows Data to be updated added without changing the
    /// timeout
    PodState<T>& operator=(const PodState<T> & copy);
    PodState<T>& operator=(const T & newData);

private:
    /* timeout which restarts each time data is recieved */
    QTimer m_stateHealthWatcher;
    T m_podState;
    void startStateHealthWatcher() override;

};

template <typename T>
PodState<T>::PodState(T initialValue, Millisecond stateHealthTimeout, QObject *parent)
    : AbstractPodState(parent),
      m_podState(initialValue)
{
    m_stateHealthWatcher.setInterval(stateHealthTimeout);
    // Once the timer times out, there is no need for it to start again
    m_stateHealthWatcher.setSingleShot(true);

    connect(&m_stateHealthWatcher, SIGNAL(timeout()), this, SIGNAL(sig_stateHealthCheckMissed()));
}

template <typename T>
void PodState<T>::slot_startStateHealthWatcher()
{
    m_stateHealthWatcher.start();
}

template<typename T>
PodState<T> &PodState<T>::operator=(const PodState<T> &copy)
{
    this->m_podState = copy.getState();
    return *this;
}

template<typename T>
PodState<T> &PodState<T>::operator=(const T &newData)
{
    this->m_podState = newData;
    return *this;
}

template <typename T>
void PodState<T>::updateState(T newState)
{
    m_podState = newState;
    m_stateHealthWatcher.start(); // This will restart the timer
}

template <typename T>
T PodState<T>::getState() const
{
    return m_podState;
}

template <typename T>
void PodState<T>::startStateHealthWatcher() {
    m_stateHealthWatcher.start();
}

#endif // PODSTATE_H
