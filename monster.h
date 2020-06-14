#ifndef MONSTER_H
#define MONSTER_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class Monster:public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Monster();
    void set_start(float X,float Y);
public slots:
    void move(float dy);
    void animation();
private:
    float start_x;
    float start_y;
    float dx = 0.5;
};

#endif // MONSTER_H
