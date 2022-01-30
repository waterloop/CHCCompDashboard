#include "logger.h"

Logger::Logger(QString fileName) {
    this->fileName_ = fileName;
}

Logger* Logger::CreateConsoleLogger() {
    return (Logger*) new ConsoleLogger();
}

Logger* Logger::CreateFileLogger() {
    return (Logger*) new FileLogger();
}

QString currentDateTime() {
    QDateTime date = QDateTime::currentDateTime();
    QString dateTime = date.toString("dd.MM.yyyy hh:mm:ss");
    return dateTime;
}

void ConsoleLogger::writeError(QString msg) {
     qInfo() << "[ERROR] " << currentDateTime() << this << ": " << msg;
}

void ConsoleLogger::writeInfo(QString msg) {
     qInfo() << "[INFO] " << currentDateTime() << this << ": " << msg;
}

void ConsoleLogger::writeWarning(QString msg) {
     qDebug() << "[WARNING] " << currentDateTime() << this << ": " << msg;
}

void FileLogger::writeError(QString msg) {
     QFile file(fileName_);
     QTextStream stream(&file);
     stream << "[ERROR] " << currentDateTime() << this << ": " << msg;
}

void FileLogger::writeInfo(QString msg) {
    QFile file(fileName_);
    QTextStream stream(&file);
    qInfo() << "[INFO] " << currentDateTime() << this << ": " << msg;
}

void FileLogger::writeWarning(QString msg) {
    QFile file(fileName_);
    QTextStream stream(&file);
    qDebug() << "[WARNING] " << currentDateTime() << this << ": " << msg;
}

void Logger::logError(QString msg) {
    writeError(msg);
}

void Logger::logInfo(QString msg) {
    writeInfo(msg);
}

void Logger::logDebug(QString msg) {
    writeWarning(msg);
}
