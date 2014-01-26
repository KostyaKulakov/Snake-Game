#include "settings.h"

Settings::Settings(const QString& namefile)
{
    fsettings = new QSettings(namefile, QSettings::IniFormat);

    showfps = fsettings->value("snake_interface/is_showfps", false).toBool();
    playmusic = fsettings->value("snake_interface/is_playsound", true).toBool();
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

bool Settings::getShowfps() const
{
    return showfps;
}

bool Settings::getPlaymusic() const
{
    return playmusic;
}
