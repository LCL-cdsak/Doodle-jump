#include "form1.h"

form1::form1()
{

}

void form1::set_pixmap(int x, int y)
{
    QPixmap pic(":/platform");
    pic.scaled(200,20);
    plat = new QGraphicsPixmapItem();
    plat->setPixmap(pic.scaledToWidth(100));
    plat->setPos(x,y);
}
