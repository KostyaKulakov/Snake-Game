#include "linksnake.h"

linkSnake::linkSnake(const float x, const float y, const direction dir)
{
    this->x   = x;
    this->y   = y;
    this->dir = dir;
}

void linkSnake::paint_link()
{
    glColor3f(1, 0, 0);

    glBegin(GL_QUADS);
        glVertex2f(x,    y);
        glVertex2f(x+10, y);
        glVertex2f(x+10, y+10);
        glVertex2f(x,    y+10);
    glEnd();
}

void linkSnake::setmatrixsize(const int width, const int height)
{
    this->width  = width;
    this->height = height;
}

void linkSnake::setX(const float x)
{
    this->x = x;
}

void linkSnake::setY(const float y)
{
    this->y = y;
}

void linkSnake::setdirection(const direction dir)
{
    this->dir = dir;
}

void linkSnake::setnextdirection(newDirection dir)
{
    ndir.push_back(dir);
}

void linkSnake::setndir(std::vector<newDirection> mdir)
{
    ndir = mdir;
}

float linkSnake::getX() const
{
    return x;
}

float linkSnake::getY() const
{
    return y;
}

direction linkSnake::getdirection() const
{
    return dir;
}

std::vector<newDirection> linkSnake::getnewdirection() const
{
    return ndir;
}

void linkSnake::bounds_checking()
{
    if(x >= width)
        x = 0;
    else if(x < 0)
        x = width-10;

    if(y >= height-25)
        y = 0;
    else if(y < 0)
        y = height-35;
}

void linkSnake::checknextdirection()
{
    if(!ndir.empty() && x == ndir.at(0).nextx && y == ndir.at(0).nexty)
    {
        this->dir = ndir.at(0).nextdir;
        ndir.erase(ndir.begin());
    }
}

bool linkSnake::isdirection(direction dir)
{
    if(this->dir == RIGHT && dir == LEFT)
        return false;
    else if(this->dir == LEFT && dir == RIGHT)
        return false;
    else if(this->dir == DOWN && dir == UP)
        return false;
    else if(this->dir == UP && dir == DOWN)
        return false;

    return true;
}

void linkSnake::down()
{
    y += 10;

    bounds_checking();
    checknextdirection();
}

void linkSnake::up()
{
    y -= 10;

    bounds_checking();
    checknextdirection();
}

void linkSnake::left()
{
    x -= 10;

    bounds_checking();
    checknextdirection();
}

void linkSnake::right()
{
    x += 10;

    bounds_checking();
    checknextdirection();
}
