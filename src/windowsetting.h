#ifndef WINDOWSETTING_H
#define WINDOWSETTING_H

#include <QDialog>

namespace Ui {
class windowSetting;
}

class windowSetting : public QDialog
{
    Q_OBJECT

public:
    explicit windowSetting(QWidget *parent = 0);
    ~windowSetting();

private slots:
    void save_setting();

private:
    Ui::windowSetting *ui;
};

#endif // WINDOWSETTING_H
