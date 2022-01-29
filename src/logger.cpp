#include "logger.h"

QString currentDateTime() {
    QDateTime date = QDateTime::currentDateTime();
    QString dateTime = date.toString("dd.MM.yyyy hh:mm:ss");
    return dateTime;
}

void Logger::log_error(QString msg) {
    if(this->output_ == 0) {
        qInfo() << currentDateTime() << this << ":" << msg; //how to print the class which is being logged
                                                            //(i.e. the class emitting the signal/that is connected)?
    } else {
        QFile file(this->fileName_);
        QTextStream stream(&file);
        stream << currentDateTime() << this << ":" << msg;
    }
}

void Logger::log_info(QString msg) {
    if(this->output_ == 0) {
        qInfo() << currentDateTime() << this << ":" << msg;
    } else {
        QFile file(this->fileName_);
        QTextStream stream(&file);
        stream << currentDateTime() << this << ":" << msg;
    }
}

void Logger::log_debug(QString msg) {
    if(this->output_ == 0) {
        qDebug() << currentDateTime() << this << ":" << msg;
    } else {
        QFile file(this->fileName_);
        QTextStream stream(&file);
        stream << currentDateTime() << this << ":" << msg;
    }
}
