#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    setFormat(QGLFormat(QGL::DoubleBuffer));
    glDepthFunc(GL_LEQUAL);

    connect(&update_timer, &QTimer::timeout, this, &GLWidget::updateGL);
    update_timer.start();

    points = fps = 0;

    VSync(true);
}

void GLWidget::initializeGL()
{
    qglClearColor(Qt::black);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, wax, way, 0, 1, 0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    calculate_fps();

    paint_interface();
}

void GLWidget::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, (GLint)w, (GLint)h);

    wax = w;
    way = h;
}

void GLWidget::VSync(const bool enable)
{
    /*QGLFormat frmt;
    frmt.setSwapInterval(enable);
    setFormat(frmt);*/
}

void GLWidget::paint_interface()
{
    qglColor(Qt::white);

    glBegin(GL_LINES);
        glVertex2f(0, way-border_bottom);
        glVertex2f(wax, way-border_bottom);
    glEnd();

    renderText(8, way-border_bottom+14, 0, QString::fromUtf8("Вы набрали %1").arg(points), QFont());
    renderText(wax-49, way-border_bottom+14, 0, QString::fromUtf8("FPS %1").arg(fps), QFont());
}

void GLWidget::calculate_fps()
{
    static int framesDone = 0;
    static unsigned last_time = clock()/1000;

    if((unsigned)clock()/1000 > last_time)
    {
        fps = framesDone;

        framesDone = 0;

        last_time = clock()/1000;
    }

    ++framesDone;
}
