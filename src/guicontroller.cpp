#include "guicontroller.h"

QVector<QString> pageNames = {"main_screen", "sensor_screen"};

GuiController::GuiController(QObject* parent)
    : QObject(parent), m_currentPageIndex(0) {}

GuiController::~GuiController() {}

uint GuiController::getCurrentPage() const {
    return m_currentPageIndex;
}

void GuiController::cycleCurrentPage(uint maxItems) {
    m_currentPageIndex = (m_currentPageIndex + 1) % maxItems;
    emit sig_currentPageChanged();
}
