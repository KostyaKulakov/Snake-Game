#pragma once
#include <QSettings>

class Settings
{
public:
    Settings(const QString& namefile);

    void setShowfps(const bool enable);
    void setPlaymusic(const bool enable);
    void setShowmatrix(const bool enable);

    bool getShowfps() const;
    bool getPlaymusic() const;
    bool getShowmatrix() const;

private:
    bool showfps = false, playmusic = true, showmatrix = false;

    QSettings *fsettings;
};

