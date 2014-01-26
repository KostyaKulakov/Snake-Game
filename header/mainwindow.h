#pragma once

#include <QMainWindow>

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
    void on_settingButton_clicked();

private:
    Ui::MainWindow *ui;
};
