#include "spring.h"

spring::spring()
{

}
void spring::move(float dy)
{
    setPos(x(),y()-dy);
    if(y()>800)
        setPos(-600,0);
}
