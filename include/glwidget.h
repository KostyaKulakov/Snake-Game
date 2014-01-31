#pragma once

#include <QGLWidget>
#include <QTimer>
#include <QKeyEvent>
#include <GL/glu.h>
#include <time.h>
#include "log.h"
#include "settings.h"
#include "snake.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit GLWidget(QWidget *parent = 0);

    Settings *getSettings() const;

private slots:
    void keyPressEvent(QKeyEvent * keyEvent);

public slots:
    void startgame();
    void endgame();

private:
    int wax, way;
    unsigned int points = 0, fps = 0;
    unsigned short step = 10;
    const unsigned border_bottom = 24;
    bool isgame = false, islost = false, stuck = true, islogo = true;

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    void paint_interface();
    void paint_matrix();
    void calculate_fps();

    void snakeactions();

    QTimer update_timer, timer_snake;
    Settings* msettings;
    Snake* snake;
};
