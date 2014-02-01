#include "registration.h"
#include "ui_windowregistration.h"

Registration::Registration(QWidget *parent, Settings *msettings) :
    QDialog(parent),
    ui(new Ui::Registration)
{
    this->msettings = msettings;
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->setupUi(this);

    ui->passwordline->setEchoMode(QLineEdit::Password);

    if(msettings->getAuthStatus())
        ui->hellolable->setText("Вход успешно выполнен: "+msettings->getName());
    else
        ui->hellolable->setText("Зарегистрируйтесь или Войдите");

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &Registration::login);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &Registration::hide);

}

Registration::~Registration()
{
    delete ui;
}

void Registration::login()
{
    mydb = new DataBase();
    mydb->connect();

    if(ui->isRegistry->isChecked())
    {
        if(mydb->auth(ui->loginline->text(), ui->passwordline->text()))
        {
            msettings->setName(ui->loginline->text());
            msettings->setPassword(QCryptographicHash::hash(ui->passwordline->text().toUtf8(), QCryptographicHash::Md5).toHex());
            msettings->setisAuth(true);

            ui->hellolable->setText("Вход успешно выполнен: "+msettings->getName());

            QMessageBox::about(0, "Авторизация", "Авторизация прошла успешна! Вход выполнен: "+ui->loginline->text());
        }
        else
            QMessageBox::about(0, "Авторизация", "Авторизация не выполнена! Неверный логин или пароль");
    }
    else
    {
        if(ui->loginline->text().size() >= 3)
        {
            if(ui->passwordline->text().size() >= 5)
            {
                if(!mydb->isuser(ui->loginline->text()))
                {
                    mydb->createaccount(ui->loginline->text(), ui->passwordline->text());

                    msettings->setName(ui->loginline->text());
                    msettings->setPassword(QCryptographicHash::hash(ui->passwordline->text().toUtf8(), QCryptographicHash::Md5).toHex());
                    msettings->setisAuth(true);

                    ui->hellolable->setText("Вход успешно выполнен: "+msettings->getName());

                    QMessageBox::about(0, "Создание Аккаунта", "Аккаунт успешно создан! Вход выполнен: "+ui->loginline->text());
                }
                else
                    QMessageBox::about(0, "Создание Аккаунта", "Данное имя уже занято");
            }
            else
                QMessageBox::about(0, "Создание Аккаунта", "Пароль должен иметь хотябы 5 символов");
        }
        else
            QMessageBox::about(0, "Создание Аккаунта", "Логни должен иметь хотябы 3 символа");
    }

    mydb->disconnect();
    delete(mydb);
}
