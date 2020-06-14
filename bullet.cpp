#include "bullet.h"

bullet::bullet()
{

}

void bullet::store_pointer(Monster *M,int index)
{
    m[index] = &M[index];
}
void bullet::if_collide()
{
    for(int i=0;i<4;i++)
        if(this->collidesWithItem(m[i]))
        {
            qDebug()<<"aaa";
        }
}
void bullet::fly()
{
    setPos(x(),y()-10);
    if(y()<0)
    {
        setPos(-100,0);
    }
}

