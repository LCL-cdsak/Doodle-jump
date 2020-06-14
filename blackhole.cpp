#include "blackhole.h"

blackhole::blackhole()
{

}
void blackhole::move_downward(float dy)
{
    setPos(x(),y()-dy);
    if(y()>800)
        setPos(-600,0);
}
