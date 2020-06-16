#include "monster2.h"


monster2::monster2()
{ 
    srand(time(NULL));
    if(rand()%2==0)
        dx = 1.5;
    else
        dx = -1.5;
}

void monster2::move(float dy)
{
    setPos(x(),y()-dy);
    if(y()>800)
        setPos(1000,0);
}

void monster2::animation()
{
    setPos(x()+dx,y());
    if(x()>540)
        dx = -dx;
    if(x()<0)
        dx = -dx;
}
