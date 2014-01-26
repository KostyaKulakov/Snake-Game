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

private:
    void resizeEvent(QResizeEvent *__e);
private slots:
    void on_settingButton_clicked();
    void resize_windows();

private:
    Ui::MainWindow *ui;
};
