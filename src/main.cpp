#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "guicontroller.h"
#include "podcontroller.h"
#include "common.h"
#include "networkcontroller/networkcontroller.h"

PodController *pod;
NetworkController *network_controller;

/*
 * This is the entry point for the application.
 * The most relavent section of this function is
 * the GUI controller, which is reponsible for patching
 * the backend controllers to the frontend so that signals
 * can be connected.
 */
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    GuiController guiController(&engine);
    pod = new PodController();
    network_controller = new NetworkController();

#ifndef DEV_SANDBOX
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
#else
    const QUrl url(QStringLiteral("qrc:/qml/dev.qml"));
#endif

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    guiController.loadBackendControllers();
    guiController.loadBackendModels();
    guiController.loadCommonNameSpace();
    engine.load(url);

    return app.exec();
}
