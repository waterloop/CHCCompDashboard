#include "guicontroller.h"

GuiController::GuiController(
        QQmlApplicationEngine *engine,
        QObject* parent
        ) : QObject(parent),
    m_engine(engine)
{
}

/*!
 * \brief GuiController::loadBackend
 * Add the backend Controllers as QML properties
 * which can be accessed through the keys assigned to
 * them directly in QML.
 */
void GuiController::loadBackendControllers()
{
    // Currently do nothing since there are no controllers.
}
