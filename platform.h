#ifndef PLATFORM_H
#define PLATFORM_H
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>

class platform
{
public:
    platform();
    virtual void set_pixmap(int x, int y);
    virtual void move();
    QGraphicsPixmapItem *plat;
};

#endif // PLATFORM_H
