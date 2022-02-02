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
    virtual void writeInfo(QString msg) = 0;
    virtual void writeWarning(QString msg) = 0;
    virtual void writeError(QString msg) = 0;

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

protected:
    void writeInfo(QString msg);
    void writeWarning(QString msg);
    void writeError(QString msg);
};

class FileLogger : public Logger {
    Q_OBJECT
    QTextStream stream;

public:
    explicit FileLogger(QString fileName);

protected:
    void writeInfo(QString msg);
    void writeWarning(QString msg);
    void writeError(QString msg);
};

#endif // LOGGER_H
