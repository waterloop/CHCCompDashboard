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

public:
    enum outputType {
        Console     = 0,
        File        = 1
    };
    Q_ENUM(outputType);

    outputType output_ = Console;
    QString fileName_ = "waterloop_desktop_log_"
            + QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");

explicit Logger(outputType output) {
    output_ = output;
};

explicit Logger(outputType output, QString fileName) {
    output_ = output;
    fileName_ = fileName;
};

public slots:
    void log_error(QString msg);

    void log_info(QString msg);

    void log_debug(QString msg);
};

#endif // LOGGER_H
