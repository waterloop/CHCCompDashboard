#include "guicontroller.h"
#include "podcontroller.h"
#include <QQmlContext>

extern PodController* pod;

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
}
