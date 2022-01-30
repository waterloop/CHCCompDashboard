#ifndef LOGGER_H
#define LOGGER_H
#include <QObject>
#include <QString>
#include <QDateTime>
#include <QtGlobal>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <cctype>


class Logger : public QObject {
    Q_OBJECT

protected:
    QString fileName_ = "waterloop_desktop_log_"
            + QDateTime::currentDateTime().toString("dd_MM_yyyy_hh_mm_ss");

    virtual void writeInfo(QString msg);
    virtual void writeWarning(QString msg);
    virtual void writeError(QString msg);

public:
    explicit Logger(QString fileName);

    static Logger* CreateFileLogger();
    static Logger* CreateConsoleLogger();

public slots:
    void logError(QString msg);

    void logInfo(QString msg);

    void logDebug(QString msg);
};


//derived classes
class ConsoleLogger : public Logger {
    Q_OBJECT

public:
    ConsoleLogger();

    void writeInfo(QString msg);
    void writeWarning(QString msg);
    void writeError(QString msg);
};

class FileLogger : public Logger {
    Q_OBJECT

public:
    FileLogger();

    void writeInfo(QString msg);
    void writeWarning(QString msg);
    void writeError(QString msg);
};

#endif // LOGGER_H
