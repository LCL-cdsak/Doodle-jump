#ifndef BLACKHOLE_H
#define BLACKHOLE_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
class blackhole:public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    blackhole();
public slots:
    void move_downward(float dy);
};

#endif // BLACKHOLE_H
