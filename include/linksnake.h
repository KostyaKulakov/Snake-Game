#pragma once
#include <GL/gl.h>
#include <QColor>
#include <vector>
#include <QtOpenGL>

enum direction
{
    UP, DOWN, LEFT, RIGHT
};

struct newDirection
{
    float nextx, nexty;
    direction nextdir;
};

class linkSnake
{
public:
    linkSnake(const float x, const float y, const direction dir);

    void paint_link();

    void setmatrixsize(const int width, const int height);
    void setX(const float x);
    void setY(const float y);
    void setdirection(const direction dir);
    void setnextdirection(newDirection newdir);
    void setndir(std::vector<newDirection> mdir);

    float     getX()         const;
    float     getY()         const;
    direction getdirection() const;

    std::vector<newDirection> getnewdirection() const;

    void bounds_checking();
    void checknextdirection();
    bool isdirection(direction dir);

    void down();
    void up();
    void left();
    void right();

private:
    float x, y;
    int width, height;
    direction dir;
    std::vector<newDirection> ndir;
};
