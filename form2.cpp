#include "form2.h"

form2::form2()
{

}
void form2::set_pixmap(int x, int y)
{
    srand(time(NULL));
    QPixmap pic(":/platform2");
    pic.scaled(200,20);
    plat = new QGraphicsPixmapItem();
    plat->setPixmap(pic.scaledToWidth(100));
    plat->setPos(x,y);
    if(rand()%2==0)
        dx = 1.5;
    else
        dx = -1.5;
}

void form2::move()
{
    if(plat->x()<0||plat->x()>500)
        dx = -dx;
    plat->setPos(plat->x()-dx,plat->y());
}
