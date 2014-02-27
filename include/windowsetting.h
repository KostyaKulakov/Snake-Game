#pragma once

#include <QDialog>
#include "settings.h"

namespace Ui {
class windowSetting;
}

class windowSetting : public QDialog
{
    Q_OBJECT

public:
    explicit windowSetting(QWidget *parent = 0, Settings *msettings = 0);
    ~windowSetting();

private slots:
    void save_setting();

private:
    Ui::windowSetting *ui;
    Settings *msettings;
};
