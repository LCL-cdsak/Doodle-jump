#ifndef SPRING_H
#define SPRING_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class spring:public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    spring();
public slots:
    void move(float dy);
};

#endif // SPRING_H
