#pragma once

#include <QGLWidget>
#include <QTimer>
#include <GL/glu.h>
#include <QSettings>
#include <time.h>
#include "log.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit GLWidget(QWidget *parent = 0);

public:
    void set_isshowfps(const bool enable);
    void set_isplaymusic(const bool enable);

public:
    bool is_showfps() const;
    bool is_playmusic() const;

public:
    void update_settings();

protected:
    int wax ,way; // size windows
    unsigned int points = 0, fps = 0;
    static const unsigned border_bottom = 24;
    bool isshowfps = false, isplaymusic = true;

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

private:
    void paint_interface();
    void calculate_fps();

private:
    QTimer update_timer;
};
