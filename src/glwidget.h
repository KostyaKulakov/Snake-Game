#pragma once

#include <QGLWidget>
#include <QTimer>
#include <GL/glu.h>
#include <time.h>
#include "log.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit GLWidget(QWidget *parent = 0);

protected:
    int wax ,way; // size windows
    unsigned int points, fps;
    static const unsigned border_bottom = 24;

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

private:
    void VSync(const bool enable);
    void paint_interface();
    void calculate_fps();

private:
    QTimer update_timer;
};
