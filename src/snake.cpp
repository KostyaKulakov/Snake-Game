#include "snake.h"

Snake::Snake()
{
    foodsound = new QSound("sound/food.wav");
    endsound = new QSound("sound/end.wav");

    linkSnake first(0, 0, RIGHT);
    links.push_back(first);
}

void Snake::paint_snake()
{
    for(auto& v : links)
        v.paint_link();
}

void Snake::paint_food()
{

    if(currentfood.isbig)
        glColor3f(0, 1, 0);
    else
        glColor3f(0, 0, 1);

    glBegin(GL_QUADS);
        glVertex2f(currentfood.x,    currentfood.y);
        glVertex2f(currentfood.x+10, currentfood.y);
        glVertex2f(currentfood.x+10, currentfood.y+10);
        glVertex2f(currentfood.x,    currentfood.y+10);
    glEnd();
}

void Snake::setmatrixsize(int width, int height)
{
    for(auto& v : links)
        v.setmatrixsize(width, height);

    this->width  = width;
    this->height = height;
}

std::vector<linkSnake>& Snake::getlinks()
{
    return links;
}

void Snake::addlink()
{
    linkSnake link(links.at(links.size()-1).getX(), links.at(links.size()-1).getY(), links.at(links.size()-1).getdirection());
    link.setmatrixsize(width, height);

    link.setndir(links.at(links.size()-1).getnewdirection());

    direction currentdir = link.getdirection();

    if(currentdir == UP)
        link.down();
    else if(currentdir == DOWN)
        link.up();
    else if(currentdir == RIGHT)
        link.left();
    else
        link.right();

    links.push_back(link);
}

bool Snake::isbigfood() const
{
    return currentfood.isbig;
}

void Snake::down()
{
    if(!links.at(0).isdirection(DOWN))
        return;

    links.at(0).setdirection(DOWN);

    newDirection nxdir;
    nxdir.nextx = links.at(0).getX();
    nxdir.nexty = links.at(0).getY();
    nxdir.nextdir = DOWN;

    for(size_t i = 1; i < links.size(); ++i)
        links.at(i).setnextdirection(nxdir);
}

void Snake::up()
{
    if(!links.at(0).isdirection(UP))
        return;

    links.at(0).setdirection(UP);

    newDirection nxdir;
    nxdir.nextx = links.at(0).getX();
    nxdir.nexty = links.at(0).getY();
    nxdir.nextdir = UP;

    for(size_t i = 1; i < links.size(); ++i)
        links.at(i).setnextdirection(nxdir);
}

void Snake::left()
{
    if(!links.at(0).isdirection(LEFT))
        return;

    links.at(0).setdirection(LEFT);

    newDirection nxdir;
    nxdir.nextx = links.at(0).getX();
    nxdir.nexty = links.at(0).getY();
    nxdir.nextdir = LEFT;

    for(size_t i = 1; i < links.size(); ++i)
        links.at(i).setnextdirection(nxdir);
}

void Snake::right()
{
    if(!links.at(0).isdirection(RIGHT))
        return;

    links.at(0).setdirection(RIGHT);

    newDirection nxdir;
    nxdir.nextx = links.at(0).getX();
    nxdir.nexty = links.at(0).getY();
    nxdir.nextdir = RIGHT;

    for(size_t i = 1; i < links.size(); ++i)
        links.at(i).setnextdirection(nxdir);
}

void Snake::autostep()
{
    for(auto& v : links)
    {
        direction currentdir = v.getdirection();

        if(currentdir == UP)
            v.up();
        else if(currentdir == DOWN)
            v.down();
        else if(currentdir == RIGHT)
            v.right();
        else
            v.left();
    }
}

bool Snake::checkcollision()
{
    float headx = links.at(0).getX(),
          heady = links.at(0).getY();

    for(size_t i = 1; i < links.size(); ++i)
        if(headx == links.at(i).getX() && heady == links.at(i).getY())
            return true;

    return false;
}

bool Snake::checkfood()
{
    float headx = links.at(0).getX(),
          heady = links.at(0).getY();

    if(headx == currentfood.x && heady == currentfood.y)
        return true;

    return false;
}

void Snake::generatefood()
{
    srand(time(NULL));

    if(cntfood == 5)
    {
        currentfood.isbig = true;
        cntfood = 0;
    }
    else
        currentfood.isbig = false;

    currentfood.x = (rand()%(width/10))*10;
    currentfood.y = (rand() % ((height-24))/10)*10;
    ++cntfood;

}

void Snake::playfoodmusic()
{
    foodsound->play();
}

void Snake::playgameovermusic()
{
    endsound->play();
}
