#ifndef MONSTER2_H
#define MONSTER2_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class monster2:public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    monster2();
    void set_start(float X,float Y);
public slots:
    void move(float dy);
    void animation();
private:
    float start_x;
    float start_y;
    float dx;


};

#endif // MONSTER2_H
