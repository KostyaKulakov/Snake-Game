#pragma once
#include <QSettings>

class Settings
{
public:
    Settings(const QString& namefile);

    void setShowfps(const bool enable);
    void setPlaymusic(const bool enable);

    bool getShowfps() const;
    bool getPlaymusic() const;

private:
    bool showfps = false, playmusic = true;

    QSettings *fsettings;
};

