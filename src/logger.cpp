#include "logger.h"

//FileLogger constructor to create the file and stream
FileLogger::FileLogger(QString fileName) {
    QFile file(fileName);
    stream.setDevice(&file);
}

//Generators
Logger* Logger::CreateConsoleLogger() {
    return (Logger*) new ConsoleLogger();
}

Logger* Logger::CreateFileLogger(QString fileName = "waterloop_desktop_log_"
                                 + QDateTime::currentDateTime().toString("dd_MM_yyyy_hh_mm_ss") + ".txt") {
    return (Logger*) new FileLogger(fileName);
}

//Function to get the current date and time
QString currentDateTime() {
    QDateTime date = QDateTime::currentDateTime();
    QString dateTime = date.toString("dd.MM.yyyy hh:mm:ss");
    return dateTime;
}

//Virtual functions
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
    stream << "[ERROR] " << currentDateTime() << this << ": " << msg;
}

void FileLogger::writeInfo(QString msg) {
    stream << "[INFO] " << currentDateTime() << this << ": " << msg;
}

void FileLogger::writeWarning(QString msg) {
    stream << "[WARNING] " << currentDateTime() << this << ": " << msg;
}

//Slots
void Logger::logError(QString msg) {
    writeError(msg);
}

void Logger::logInfo(QString msg) {
    writeInfo(msg);
}

void Logger::logDebug(QString msg) {
    writeWarning(msg);
}
