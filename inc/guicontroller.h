#ifndef GUICONTROLLER_H
#define GUICONTROLLER_H

#include <QObject>
#include <QString>
#include <QVector>

/**
 * @brief The GuiController class
 * Stores all of the state for the frontend
 */
class GuiController : public QObject {
    Q_OBJECT
    Q_PROPERTY(uint currentPage READ getCurrentPage NOTIFY sig_currentPageChanged)

public:
    explicit GuiController(QObject* parent=nullptr);
    ~GuiController();

    uint getCurrentPage() const;

    Q_INVOKABLE void cycleCurrentPage(uint maxItems );

//public slots:
private:
    uint m_currentPageIndex;
//private slots:
signals:
    void sig_currentPageChanged();
};

#endif // GUICONTROLLER_H
