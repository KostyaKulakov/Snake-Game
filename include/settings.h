#pragma once
#include <QSettings>

class Settings
{
public:
    Settings(const QString& namefile);

    void setShowfps(const bool enable);
    void setPlaymusic(const bool enable);
    void setShowmatrix(const bool enable);
    void setName(const QString name);
    void setPassword(const QByteArray password);
    void setisAuth(const bool auth);

    bool getShowfps() const;
    bool getPlaymusic() const;
    bool getShowmatrix() const;
    QString getName() const;
    QByteArray getPassword() const;
    bool    getAuthStatus() const;

private:
    bool showfps = false, playmusic = true, showmatrix = false, auth = false;
    QString name;
    QByteArray password;

    QSettings *fsettings;
};

