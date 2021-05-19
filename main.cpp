#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "guicontroller.h"

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
    GuiController guiController(engine);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
