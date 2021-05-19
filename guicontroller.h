#ifndef GUICONTROLLER_H
#define GUICONTROLLER_H

#include <QObject>
#include <QQmlApplicationEngine>


/*
 * class GuiController
 * The Gui Controller is responsible for connecting backend C++ code with
 * the frontend QML Code. It does this through the qml engine reference.
 */
class GuiController : public QObject
{
    Q_OBJECT
public:
    explicit GuiController(QQmlApplicationEngine *engine, QObject *parent = nullptr);

    // Using the Engine load all of the singleton controllers
    void loadBackendControllers();

private:
    QQmlApplicationEngine *m_engine;
};

#endif // GUICONTROLLER_H
