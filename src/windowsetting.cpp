#include "windowsetting.h"
#include "ui_windowsetting.h"
#include <QSettings>

windowSetting::windowSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::windowSetting)
{
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->setupUi(this);

    QSettings *settings = new QSettings("settings.conf", QSettings::IniFormat);
    ui->isfpsBox->setChecked(settings->value("snake_interface/is_showfps", false).toBool());
    ui->issoundBox->setChecked(settings->value("snake_interface/is_playsound", true).toBool());

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &windowSetting::save_setting);
}

windowSetting::~windowSetting()
{
    delete ui;
}

void windowSetting::save_setting()
{
    QSettings *settings = new QSettings("settings.conf", QSettings::IniFormat);

    settings->setValue("snake_interface/is_showfps", ui->isfpsBox->isChecked());
    settings->setValue("snake_interface/is_playsound", ui->issoundBox->isChecked());

    settings->sync();
}
