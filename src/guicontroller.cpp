#include "guicontroller.h"
#include "podcontroller.h"
#include "networkcontroller/networkcontroller.h"
#include <QQmlContext>
#include "common.h"

GuiController::GuiController(
        QQmlApplicationEngine *engine,
        QObject* parent
        )
    : QObject(parent),
      m_engine(engine)
{
}

/*!
 * \brief GuiController::loadBackendControllers
 * Add the backend Controllers as QML properties
 * which can be accessed through the keys assigned to
 * them directly in QML.
 */
void GuiController::loadBackendControllers()
{
    m_engine->rootContext()->setContextProperty("pod", pod);
    m_engine->rootContext()->setContextProperty("network", network_controller);
}

/*!
 * \brief GuiController::loadBackendModels
 * Backend models are data interfaces which
 * can be used to fill a QML View.
 */
void GuiController::loadBackendModels()
{
    m_engine->rootContext()->setContextProperty("liveData", pod->getLiveData());
}

/*!
 * \brief GuiController::loadCommonNameSpace
 * Loading the common namespace into the qml
 * space enables us to reference enums that are
 * defined in the common namespace inside of QML.
 */
void GuiController::loadCommonNameSpace()
{
    qmlRegisterUncreatableMetaObject(
        common::staticMetaObject,   // Meta Object Created by Q_NAMESPACE macro
        "waterloop.common",         // import statement
        1, 0,                       // major and minor version of import
        "Common",                   // Name in QML
        "Error: Common is registered as an uncreatable namespace" // Error if someone tries to create an object from the common namespace
    );
}
