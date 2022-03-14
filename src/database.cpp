#include "inc/database.h"

Database::Database() {
    QSqlDatabase m_db = QSqlDatabase::addDatabase("QPSQL");
    m_db.setHostName("localhost");
    m_db.setDatabaseName("timeseries_db");
    m_db.setPort(5432);
    m_db.setUserName("postgres");
    m_db.setPassword("testtest0987");

    if(!m_db.open()) {
        qDebug() << "Issue opening the database";
    }

    m_db.close();
}

Database::~Database() {
    m_db.close();
    m_db.removeDatabase("timeseries_db");
}

void Database::insertData(int field_id, float telemetry_data, QString datetime) {
    if(!m_db.open()) {
        qDebug() << "Issue opening the database";
    }

    QSqlQuery qry;
    qry.prepare("INSERT INTO telemetry ("
                "field_id,"
                "data,"
                "date)"
                "VALUES (?,?,?);");

    qry.addBindValue(field_id);
    qry.addBindValue(telemetry_data);
    qry.addBindValue(QDateTime::fromString(datetime, "mm-dd-yyyy-hh-mm-ss"));

    if(!qry.exec()) {
        qDebug() << "Error inputting data into database";
    }

    m_db.close();
}
