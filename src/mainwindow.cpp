#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "windowsetting.h"

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

void MainWindow::on_settingButton_clicked()
{
    windowSetting msetting;

    msetting.exec();

    ui->glWidgetSnake->update_settings();
}
