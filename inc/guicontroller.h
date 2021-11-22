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

    // Uses the Engine to load all backend DataModels
    void loadBackendModels();

    // Loads the common namespace into QML engine
    void loadCommonNameSpace();

    // register custom classes as datatypes in the meta system
    void registerCustomMetaTypes();
private:
    QQmlApplicationEngine *m_engine;
};

#endif // GUICONTROLLER_H
