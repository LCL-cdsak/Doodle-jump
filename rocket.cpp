#include "rocket.h"

rocket::rocket()
{

}
void rocket::move(float dy)
{
    setPos(x(),y()-dy);
    if(y()>800)
        setPos(-600,0);
}
