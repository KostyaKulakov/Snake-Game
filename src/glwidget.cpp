#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    connect(&update_timer, &QTimer::timeout, this, &GLWidget::updateGL);
    update_timer.start();

    VSync(true);
}

void GLWidget::initializeGL()
{
    glClearColor(0, 0, 0, 0);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1,1,1);

    QFont shrift("Times", 12, QFont::Bold);
    renderText(-0.5, 0, 0, "Test, text", shrift);
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)w/h, 0.2,  1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,5, 0,0,0, 0,1,0);
}

void GLWidget::VSync(const bool enable)
{
    QGLFormat frmt;
    frmt.setSwapInterval(enable);
    setFormat(frmt);
}
