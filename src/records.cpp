#include "records.h"
#include "ui_windowrecords.h"
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QTableView>

Records::Records(QWidget *parent, DataBase *db) :
    QDialog(parent),
    ui(new Ui::Records)
{
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->setupUi(this);

    this->mydb = db;

    std::vector<Recordtable> rcv = mydb->getrecordtable();

    for(auto& v : rcv)
    {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());

        QTableWidgetItem *name = new QTableWidgetItem(v.name);
        QTableWidgetItem *record = new QTableWidgetItem(v.record);

        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, name);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, record);

    }
}

Records::~Records()
{
    delete ui;
}
