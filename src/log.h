#pragma once

#include <QString>
#include <QFile>
#include <QTextStream>
#include <ctime>
#include <QMessageBox>

enum LogLevel
{
    logInfo= 0,
    logWarning,
    logError
};

class Log
{
public:
    Log();

public:
    void push_log(QString sender, QString text, LogLevel level);

private:
    QString getCurrentTime();
};
