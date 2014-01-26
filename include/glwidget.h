#pragma once

#include <QGLWidget>
#include <QTimer>
#include <GL/glu.h>
#include <time.h>
#include "log.h"
#include "settings.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit GLWidget(QWidget *parent = 0);

    Settings *getSettings() const;

private:
    int wax, way;
    unsigned int points = 0, fps = 0;
    unsigned short step = 10;
    const unsigned border_bottom = 24;

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    void paint_interface();
    void calculate_fps();

    QTimer update_timer;
    Settings* msettings;
};
