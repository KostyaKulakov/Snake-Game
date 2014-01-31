#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    msettings = new Settings("config.conf");

    setFormat(QGLFormat(QGL::DoubleBuffer));
    glDepthFunc(GL_LEQUAL);

    connect(&update_timer, &QTimer::timeout, this, &GLWidget::updateGL);
    connect(&timer_snake,  &QTimer::timeout, this, &GLWidget::snakeactions);
    update_timer.start();
}

Settings *GLWidget::getSettings() const
{
    return msettings;
}

void GLWidget::keyPressEvent(QKeyEvent *keyEvent)
{
    if(stuck)
    {
        stuck = false;

        if(keyEvent->key() == Qt::Key_Up)
            snake->up();
        else if(keyEvent->key() == Qt::Key_Down)
            snake->down();
        else if(keyEvent->key() == Qt::Key_Left)
            snake->left();
        else if(keyEvent->key() == Qt::Key_Right)
            snake->right();
        else if(keyEvent->key() == Qt::Key_Plus)
            snake->generatefood();

        stuck = true;
    }
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

    if(isgame)
    {
        snake->paint_snake();
        snake->paint_food();
    }
    else if(islogo)
    {
        qglColor(Qt::green);
        renderText((wax/2)-80, (way-border_bottom)/2, 0, "Snake - Классическая Змейка", QFont());
    }
    else if(islost && !isgame)
    {
        qglColor(Qt::red);
        renderText((wax/2)-100, (way-border_bottom)/2, 0, QString::fromUtf8("Игра закончена, Вы набрали %1 очков").arg(points), QFont());
    }

    if(msettings->getShowmatrix())
        paint_matrix();

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

    if(snake != NULL)
        snake->setmatrixsize(wax, way);
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

void GLWidget::paint_matrix()
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

void GLWidget::startgame()
{
    points = 0;
    snake = new Snake();
    snake->setmatrixsize(wax, way);
    isgame = true;
    islogo = false;

    setFocus();
    snake->generatefood();
    timer_snake.start(50);
}

void GLWidget::endgame()
{
    if(msettings->getPlaymusic())
        snake->playgameovermusic();

    isgame = false;
    islost = true;

    timer_snake.stop();
    delete(snake);
}

void GLWidget::snakeactions()
{
    snake->autostep();

    if(snake->checkcollision())
        endgame();

    if(snake->checkfood())
    {
        if(msettings->getPlaymusic())
            snake->playfoodmusic();

        snake->generatefood();
        snake->addlink();

        if(snake->isbigfood())
            points += 100;
        else
            points += 10;
    }
}
