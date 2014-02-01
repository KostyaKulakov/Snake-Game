#include "database.h"

DataBase::DataBase()
{
    db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName(hostname);
    db.setPort(port);
    db.setDatabaseName(dbname);
    db.setUserName(user);
    db.setPassword(password);
}

void DataBase::connect()
{
    if(!db.open())
        QMessageBox::critical(0, QObject::tr("Database"),
                              db.lastError().text());
}

void DataBase::disconnect()
{
    QSqlDatabase::removeDatabase(db.connectionName());
    db.close();
}

bool DataBase::createaccount(QString name, QString password)
{
    if(isuser(name))
        return false;

    QSqlQuery query(db);

    query.prepare("INSERT INTO account (name, password) "
                                        "VALUES (:name, :password)");
    query.bindValue(":name", name);
    query.bindValue(":password", QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Md5).toHex());

    if(!query.exec())
    {
        QMessageBox::critical(0, QObject::tr("Database insert acc"),
                              query.lastError().text());

        return false;
    }

    updaterecord(name, 0, true);

    return true;
}

bool DataBase::auth(QString name, QString password)
{
    QSqlQuery query(db);
    query.prepare("SELECT * FROM account WHERE name=:name AND password=:password LIMIT 1");

    query.bindValue(":name", name);
    query.bindValue(":password", QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Md5).toHex());

    if(!query.exec())
    {
        QMessageBox::critical(0, QObject::tr("Database"),
                              query.lastError().text());
        return false;
    }

    return query.next();
}

bool DataBase::auth(QString name, QByteArray password)
{
    QSqlQuery query(db);
    query.prepare("SELECT * FROM account WHERE name=:name AND password=:password LIMIT 1");

    query.bindValue(":name", name);
    query.bindValue(":password", password);

    if(!query.exec())
    {
        QMessageBox::critical(0, QObject::tr("Database"),
                              query.lastError().text());
        return false;
    }

    return query.next();
}

bool DataBase::updaterecord(QString name, unsigned record, bool newacc)
{
    QSqlQuery query(db);

    unsigned id = getidfromname(name);

    if(newacc)
        query.prepare("INSERT INTO record (userid, record) "
                                            "VALUES (:userid, :record)");
    else
        query.prepare("UPDATE record SET record=:record "
                                            "WHERE(userid=:userid)");

    query.bindValue(":userid", id);
    query.bindValue(":record", record);

    if(!query.exec())
    {
        QMessageBox::critical(0, QObject::tr("Database insert rec"),
                              query.lastError().text());

        return false;
    }

    return true;
}

bool DataBase::isuser(QString name)
{
    QSqlQuery query(db);
    query.prepare("SELECT * FROM account WHERE name=:name LIMIT 1");

    query.bindValue(":name", name);

    if(!query.exec())
    {
        QMessageBox::critical(0, QObject::tr("Database"),
                              query.lastError().text());
        return false;
    }

    return query.next();
}

unsigned DataBase::getidfromname(QString name)
{
    QSqlQuery query(db);

    query.prepare("SELECT * FROM account WHERE name=:name LIMIT 1");

    query.bindValue(":name", name);

    if(!query.exec())
    {
        QMessageBox::critical(0, QObject::tr("Database select"),
                              query.lastError().text());

        return false;
    }

    query.next();

    return query.value(0).toUInt();
}

QString DataBase::getnamefromid(unsigned id)
{
    QSqlQuery query(db);

    query.prepare("SELECT * FROM account WHERE id=:userid LIMIT 1");

    query.bindValue(":userid", id);

    if(!query.exec())
        QMessageBox::critical(0, QObject::tr("Database select"),
                              query.lastError().text());

    query.next();

    return query.value(1).toString();
}

Recordtable DataBase::getrecord(unsigned id)
{
    QSqlQuery query(db);

    query.prepare("SELECT * FROM record WHERE userid=:userid LIMIT 1");

    query.bindValue(":userid", id);

    if(!query.exec())
        QMessageBox::critical(0, QObject::tr("Database select"),
                              query.lastError().text());

    query.next();

    Recordtable rc;

    rc.record = query.value(2).toString();
    rc.name = getnamefromid(id);

    return rc;
}

std::vector<Recordtable> DataBase::getrecordtable()
{
    QSqlQuery query(db);
    query.exec("SELECT * FROM record ORDER BY record DESC");

    std::vector<Recordtable> rcv;

    while(query.next())
        rcv.push_back(getrecord(query.value(1).toInt()));

    return rcv;
}
