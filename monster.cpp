#include "monster.h"

Monster::Monster()
{

}

void Monster::set_start(float X , float Y)
{
    start_x = X;
    start_y = Y;
}

void Monster::move(float dy)
{
    setPos(x(),y()-dy);
    if(y()>800)
        setPos(-600,0);
}

void Monster::animation()
{
    setPos(x()+dx,y());
    if(x()>start_x+8)
        dx = -dx;
    if(x()<start_x-8)
        dx = -dx;
}
