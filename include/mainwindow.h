#pragma once

#include <QMainWindow>
#include <QKeyEvent>
#include "records.h"
#include "registration.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

private:
    void resizeEvent(QResizeEvent *e);

private slots:
    void opensettings();
    void openrecords();
    void openregistration();
    void installsizepolice();

private:
    Ui::MainWindow *ui;
};
