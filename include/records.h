#pragma once

#include <QDialog>
#include "database.h"

namespace Ui {
class Records;
}

class Records : public QDialog
{
    Q_OBJECT

public:
    explicit Records(QWidget *parent = 0, DataBase *db = 0);
    ~Records();

private:
    Ui::Records *ui;
    DataBase* mydb;
};
