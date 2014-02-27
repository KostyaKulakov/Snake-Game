#pragma once
#include <vector>
#include <QTimer>
#include <QSignalMapper>
#include <ctime>
#include "linksnake.h"
#include <QSound>

struct food
{
    float x = 10, y = 0;
    bool isbig;
};

class Snake
{
public:
    Snake();

    void paint_snake();
    void paint_food();

    void setmatrixsize(int width, int height);
    std::vector<linkSnake>& getlinks();

    void addlink();

    bool isbigfood() const;

    void move(direction dir);
    void autostep();

    bool checksnake(float x, float y);
    bool checkcollision();
    bool checkfood();

    void generatefood();

    void playfoodmusic();
    void playgameovermusic();

private:
    std::vector<linkSnake> links;
    QSound* foodsound, *endsound;
    food currentfood;
    bool test = true;
    unsigned cntfood = 0;
    int width, height;
};
