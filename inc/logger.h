#ifndef LOGGER_H
#define LOGGER_H
#include <QObject>
#include <QString>
#include <QDateTime>


class Logger : public QObject {
    Q_OBJECT //what does this do?

public:
    QString outputType_ = "console"; //default to the console?
    QString fileName_ = "waterloop_desktop_log_"
            + QDateTime::currentDateTime().toString("yyyy_MM_dd_HH_mm");

//    enum outputType {
//        File,
//        Console
//    };

explicit Logger(QString outputType) { //is explicit necessary?
    outputType_ = outputType;
};

explicit Logger(QString outputType, QString fileName) {
    outputType_ = outputType;
    fileName_ = fileName;
};

public slots:
    void log_error(QString msg);

    void log_info(QString msg);

    void log_debug(QString msg);
};

#endif // LOGGER_H
