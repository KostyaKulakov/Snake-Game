#pragma once

#include <QMainWindow>
#include <QGLWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_settingButton_clicked();

private:
    Ui::MainWindow *ui;
};
