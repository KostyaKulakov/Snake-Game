#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "windowsetting.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->exitButton,     &QPushButton::clicked, this, &QApplication::quit);
    connect(ui->settingButton,  &QPushButton::clicked, this, &MainWindow::opensettings);
    connect(ui->recordButton,   &QPushButton::clicked, this, &MainWindow::openrecords);
    connect(ui->regButton,      &QPushButton::clicked, this, &MainWindow::openregistration);
    connect(ui->startgameButton,&QPushButton::clicked, ui->glWidgetSnake, &GLWidget::startgame);
    connect(ui->startgameButton,&QPushButton::clicked, this, &MainWindow::installsizepolice);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    unsigned w = this->width()-103;
    unsigned h = this->height()-22;

    if(w % 10 != 0 || (h % 10 == 0 || h % 5 != 0))
    {
        w /= 10;
        w *= 10;

        h /= 10;
        h *= 10;
        h += 5;

        resize(w+103, h+22);
    }
}

void MainWindow::opensettings()
{
    windowSetting msetting(0, ui->glWidgetSnake->getSettings());

    msetting.exec();

    ui->glWidgetSnake->setFocus();
}

void MainWindow::openrecords()
{
    Records mrecords;

    mrecords.exec();
    ui->glWidgetSnake->setFocus();
}

void MainWindow::openregistration()
{
    Registration mreg(0, ui->glWidgetSnake->getSettings());

    mreg.exec();

    ui->glWidgetSnake->setFocus();
}

void MainWindow::installsizepolice()
{
    setMaximumHeight(this->height());
    setMaximumWidth(this->width());
    setMinimumHeight(this->height());
    setMinimumWidth(this->width());
}
