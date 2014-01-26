#include "glwidget.h"
#include <QImage>
#include <QPixmap>

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    msettings = new Settings("config.conf");

    setFormat(QGLFormat(QGL::DoubleBuffer));
    glDepthFunc(GL_LEQUAL);

    connect(&update_timer, &QTimer::timeout, this, &GLWidget::updateGL);
    update_timer.start();
}

Settings *GLWidget::getSettings() const
{
    return msettings;
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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    qglColor(Qt::red);
    renderText(-0.2, 0, 0, "Snake", QFont("Times", 30));

    glOrtho(0, wax, way, 0, 1, 0);

    if(msettings->getShowmatrix())
    {
        qglColor(Qt::gray);

        for(unsigned int i = 0; i < way-border_bottom; i += step)
        {
            glBegin(GL_LINES);
                glVertex2f(0, i);
                glVertex2f(wax, i);
            glEnd();
        }

        for(int i = 0; i < wax; i += step)
        {
            glBegin(GL_LINES);
                glVertex2f(i, 0);
                glVertex2f(i, way-border_bottom);
            glEnd();
        }
    }
    if(msettings->getShowfps())
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

void GLWidget::paint_interface()
{
    qglColor(Qt::white);

    glBegin(GL_LINES);
        glVertex2f(0, way-border_bottom);
        glVertex2f(wax, way-border_bottom);
    glEnd();

    renderText(8, way-border_bottom+14, 0, QString::fromUtf8("Вы набрали %1 очков").arg(points), QFont());

    if(msettings->getShowfps())
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
