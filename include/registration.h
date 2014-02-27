#pragma once
#include "settings.h"
#include "database.h"
#include <QDialog>
#include <QMessageBox>

namespace Ui {
class Registration;
}

class Registration : public QDialog
{
    Q_OBJECT

public:
    explicit Registration(QWidget *parent = 0, Settings *msettings = 0, DataBase *db = 0);
    ~Registration();

private slots:
    void login();

private:
    Ui::Registration *ui;
    Settings *msettings;
    DataBase* mydb;
};
