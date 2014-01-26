#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "windowsetting.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->exitButton, &QPushButton::clicked, this, &QApplication::quit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *__e)
{
    unsigned w = this->width()-103;
    unsigned h = this->height()-22;

    if(w % 10 != 0 || h % 5 != 0)
    {
        w /= 10;
        w *= 10;

        h /= 10;
        h *= 10;
        h += 5;

        resize(w+103, h+22);
    }
}

void MainWindow::on_settingButton_clicked()
{
    windowSetting msetting;

    msetting.exec();

    ui->glWidgetSnake->update_settings();
}

void MainWindow::resize_windows()
{

}
