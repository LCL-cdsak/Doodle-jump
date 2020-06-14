#ifndef ROCKET_H
#define ROCKET_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>


class rocket:public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    rocket();
public slots:
    void move(float dy);
};

#endif // ROCKET_H
