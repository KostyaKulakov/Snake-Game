#pragma once
#include <string>
#include <QSqlDatabase>
#include <QtSql>
#include <QSqlError>
#include <QSqlQuery>
#include <QCryptographicHash>
#include <QMessageBox>
#include <vector>
#include "recordstruct.h"

class DataBase
{
public:
    DataBase();

    void connect();
    void disconnect();
    bool createaccount(QString name, QString password);
    bool auth(QString name, QString password);
    bool auth(QString name, QByteArray password);
    bool updaterecord(QString name, unsigned record, bool newacc = false);
    bool isuser(QString name);
    unsigned getidfromname(QString name);
    QString  getnamefromid(unsigned id);
    Recordtable getrecord(unsigned id);
    std::vector<Recordtable> getrecordtable();

private:
    QSqlDatabase db;
    const QString hostname = "82.146.52.29";
    const unsigned port    =  3306;
    const QString dbname   = "records";
    const QString user     = "programm";
    const QString password = "programm";
};
