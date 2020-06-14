#ifndef BULLET_H
#define BULLET_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include "monster.h"
#include <QtDebug>
class bullet:public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    bullet();
    void store_pointer(Monster *M,int index);
public slots:
    void fly();
    void if_collide();
private:
    Monster *m[4];
};

#endif // BULLET_H
