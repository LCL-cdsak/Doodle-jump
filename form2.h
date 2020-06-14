#ifndef FORM2_H
#define FORM2_H
#include<platform.h>
#include<ctime>
class form2:public platform
{
public:
    form2();
    void set_pixmap(int x, int y);
    void move();
    float dx;
};

#endif // FORM2_H
