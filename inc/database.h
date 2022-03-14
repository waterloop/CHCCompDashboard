#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QString>
#include "QtSql"


class Database : public QObject
{
    Q_OBJECT

private:
    QSqlDatabase m_db;

public:
    Database();
    ~Database();
    void insertData(int field_id, float telemetry_data, QString datetime);
};


#endif // DATABASE_H
