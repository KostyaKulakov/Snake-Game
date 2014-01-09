#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GLWidget::updateGL);
    timer->start(750);
}

void GLWidget::initializeGL()
{
    glClearColor(1, 1, 0, 1);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1, 0, 0);
    glBegin(GL_TRIANGLES);
        glVertex3f(-0.5, -0.5, 0);
        glVertex3f( 0.5, -0.5, 0);
        glVertex3f( 0.0,  0.5, 0);
    glEnd();
}

void GLWidget::resizeGL(int w, int h)
{

}
