#include "inc/guicontroller.h"
#include "inc/podcontroller.h"
#include "inc/networkcontroller.h"
#include <QQmlContext>
#include "inc/common.h"

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
