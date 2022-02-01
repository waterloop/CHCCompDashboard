#ifndef LOGGER_H
#define LOGGER_H
#include <QObject>
#include <QString>
#include <QDateTime>
#include <QtGlobal>
#include <QDebug>
#include <QFile>
#include <QTextStream>

class Logger : public QObject {
    Q_OBJECT

protected:
    virtual void writeInfo(QString msg);
    virtual void writeWarning(QString msg);
    virtual void writeError(QString msg);

public:
    static Logger* CreateConsoleLogger();
    static Logger* CreateFileLogger(QString fileName);

public slots:
    void logError(QString msg);
    void logInfo(QString msg);
    void logDebug(QString msg);
};


//child classes
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
    QTextStream stream;

public:
    explicit FileLogger(QString fileName);

    void writeInfo(QString msg);
    void writeWarning(QString msg);
    void writeError(QString msg);
};

#endif // LOGGER_H
