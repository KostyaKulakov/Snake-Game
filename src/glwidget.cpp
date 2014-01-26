#include "glwidget.h"
#include <QImage>
#include <QPixmap>

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    update_settings();

    setFormat(QGLFormat(QGL::DoubleBuffer));
    glDepthFunc(GL_LEQUAL);

    connect(&update_timer, &QTimer::timeout, this, &GLWidget::updateGL);
    update_timer.start();

    resize(640, 480);
}

void GLWidget::set_isshowfps(const bool enable)
{
    isshowfps = enable;
}

void GLWidget::set_isplaymusic(const bool enable)
{
    isplaymusic = enable;
}

bool GLWidget::is_showfps() const
{
    return isshowfps;
}

bool GLWidget::is_playmusic() const
{
    return isplaymusic;
}

void GLWidget::update_settings()
{
    QSettings *settings = new QSettings("settings.conf", QSettings::IniFormat);

    set_isshowfps(settings->value("snake_interface/is_showfps", false).toBool());
    set_isplaymusic(settings->value("snake_interface/is_playsound", true).toBool());
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

    if(isshowfps)
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

    renderText(8, way-border_bottom+14, QString::fromUtf8("Вы набрали %1 очков").arg(points), QFont());

    if(isshowfps)
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
