#include "settings.h"

Settings::Settings(const QString& namefile)
{
    fsettings = new QSettings(namefile, QSettings::IniFormat);

    showfps    = fsettings->value("snake_interface/is_showfps", false).toBool();
    playmusic  = fsettings->value("snake_interface/is_playsound", true).toBool();
    showmatrix = fsettings->value("snake_interface/is_showmatrix", false).toBool();
    name       = fsettings->value("db/login", "").toString();
    password   = fsettings->value("db/password").toByteArray();
    auth       = fsettings->value("db/auth", false).toBool();
}

void Settings::setShowfps(const bool enable)
{
     showfps = enable;

     fsettings->setValue("snake_interface/is_showfps", enable);

     fsettings->sync();
}

void Settings::setPlaymusic(const bool enable)
{
    playmusic = enable;

    fsettings->setValue("snake_interface/is_playsound", enable);

    fsettings->sync();
}

void Settings::setShowmatrix(const bool enable)
{
    showmatrix = enable;

    fsettings->setValue("snake_interface/is_showmatrix", enable);

    fsettings->sync();
}

void Settings::setName(const QString name)
{
    this->name = name;

    fsettings->setValue("db/login", name);

    fsettings->sync();
}

void Settings::setPassword(const QByteArray password)
{
    this->password = password;

    fsettings->setValue("db/password", password);

    fsettings->sync();
}

void Settings::setisAuth(const bool auth)
{
    this->auth = auth;

    fsettings->setValue("db/auth", auth);

    fsettings->sync();
}

bool Settings::getShowfps() const
{
    return showfps;
}

bool Settings::getPlaymusic() const
{
    return playmusic;
}

bool Settings::getShowmatrix() const
{
    return showmatrix;
}

QString Settings::getName() const
{
    return name;
}

QByteArray Settings::getPassword() const
{
    return password;
}

bool Settings::getAuthStatus() const
{
    return auth;
}
