#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent, DataBase *db) :
    QGLWidget(parent)
{
    mydb = db;
    msettings = new Settings("config.conf");

    srand(time(NULL));

    setFormat(QGLFormat(QGL::DoubleBuffer));
    glDepthFunc(GL_LEQUAL);

    connect(&update_timer, &QTimer::timeout, this, &GLWidget::updateGL);
    connect(&timer_snake,  &QTimer::timeout, this, &GLWidget::snakeactions);
    update_timer.start(15);
}

Settings *GLWidget::getSettings() const
{
    return msettings;
}

void GLWidget::keyPressEvent(QKeyEvent *keyEvent)
{
    if(stuck && isgame)
    {
        stuck = false;

        if(keyEvent->key() == Qt::Key_Up)
            snake->move(UP);
        else if(keyEvent->key() == Qt::Key_Down)
            snake->move(DOWN);
        else if(keyEvent->key() == Qt::Key_Left)
            snake->move(LEFT);
        else if(keyEvent->key() == Qt::Key_Right)
            snake->move(RIGHT);
        else if(keyEvent->key() == Qt::Key_Escape)
            endgame();

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

    if(snake != NULL && isgame)
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

bool GLWidget::getisgame() const
{
    return isgame;
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

    if(msettings->getAuthStatus())
    {
        if(mydb->auth(msettings->getName(), msettings->getPassword()))
        {
            if(mydb->getrecord(mydb->getidfromname(msettings->getName())).record.toUInt() < points)
            {
                mydb->updaterecord(msettings->getName(), points);
                QMessageBox::about(0, "Сохранение рекорда", "Вы поставили новый рекорд! Поздравляем!");
            }
        }
        else
                QMessageBox::about(0, "Сохранение рекорда", "Рекорд не сохранен, не верный логин или пароль");
    }
}

void GLWidget::snakeactions()
{
    snake->autostep();

    if(snake->checkcollision())
    {
        endgame();

        return;
    }

    if(snake->checkfood())
    {
        if(msettings->getPlaymusic())
            snake->playfoodmusic();

        snake->addlink();

        if(snake->isbigfood())
            points += 50 + ((rand()%200)/10)*10;
        else
            points += 10;

        snake->generatefood();
    }
}

void GLWidget::setdb(DataBase *db)
{
    this->mydb = db;
}
