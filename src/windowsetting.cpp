#include "windowsetting.h"
#include "ui_windowsetting.h"

windowSetting::windowSetting(QWidget *parent, Settings *msettings) :
    QDialog(parent),
    ui(new Ui::windowSetting)
{
    this->msettings = msettings;

    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->setupUi(this);

    ui->isfpsBox->setChecked(msettings->getShowfps());
    ui->issoundBox->setChecked(msettings->getPlaymusic());
    ui->ismatrixBox->setChecked(msettings->getShowmatrix());

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &windowSetting::save_setting);
}

windowSetting::~windowSetting()
{
    delete ui;
}

void windowSetting::save_setting()
{
    msettings->setShowfps(ui->isfpsBox->isChecked());
    msettings->setPlaymusic(ui->issoundBox->isChecked());
    msettings->setShowmatrix(ui->ismatrixBox->isChecked());
}
