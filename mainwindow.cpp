#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <QDebug>
#include <ctime>
#include<QTransform>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),timer(new QTimer)
{
    srand(time(NULL));
    ui->setupUi(this);
    this->setWindowTitle("DOODLE JUMP!");
    end = new result;
    connect(timer,SIGNAL(timeout()),this,SLOT(jump()));
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    connect(timer,SIGNAL(timeout()),this,SLOT(set_platform()));
    connect(timer,SIGNAL(timeout()),this,SLOT(set_hazard()));
    connect(timer,SIGNAL(timeout()),this,SLOT(if_collide()));
    timer->start(8);
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,600,800);
    ui->graphicsView->setScene(scene);
    static QPixmap back(":/background");
    QPixmap pic(":/icedoodle");
    QGraphicsPixmapItem *background = new QGraphicsPixmapItem();
    background->setPixmap(back.scaledToHeight(800).scaledToWidth(600));
    background->setZValue(-2);
    scene->addItem(background);
    player = new QGraphicsPixmapItem();
    player->setPixmap(pic.scaled(100,100).transformed(QTransform().scale(-1, 1)));
    plat[0] = new form1;
    plat[0]->set_pixmap(0,770);
    scene->addItem(plat[0]->plat);
    for(int i =1;i<20;i++)//generate platform
    {
        plat[i] = new form1;
        plat[i]->set_pixmap(rand()%500,plat[i-1]->plat->y()-(rand()%200)-30);
        scene->addItem(plat[i]->plat);
    }   
    for(int i =0;i<2;i++) //generate monster
    {
        m[i] = nullptr;
        m[i] = new Monster;
        m[i]->setPixmap(QPixmap(":/Monster1").scaledToHeight(60));
        m[i]->setPos(-500,0);
        m[i]->set_start(m[i]->x(),m[i]->y());
        m[i]->connect(this,SIGNAL(monster_move(float)),m[i],SLOT(move(float)));
        m[i]->connect(timer,SIGNAL(timeout()),m[i],SLOT(animation()));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(m[i]));
    }
    for(int i =0;i<2;i++) //generate blackhole
    {
        h[i] = nullptr;
        h[i] = new blackhole;
        h[i]->setPixmap(QPixmap(":/hole").scaledToHeight(80));
        h[i]->setPos(-500,0);
        h[i]->connect(this,SIGNAL(spring_move(float)),h[i],SLOT(move_downward(float)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(h[i]));
    }
    for(int i =0;i<bullet_nember;i++) //generate bullet
    {
        b[i] = new bullet;
        b[i]->setPixmap(QPixmap(":/Dot").scaledToHeight(15));
        b[i]->setPos(player->x()+43.5,player->y()+15);
        b[i]->connect(timer,SIGNAL(timeout()), b[i] ,SLOT(fly()));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(b[i]));
    }
    for(int i =0;i<5;i++) //generate spring
    {
        s[i] = new spring;
        s[i]->setPos(-500,0);
        s[i]->connect(this,SIGNAL(spring_move(float)),s[i],SLOT(move(float)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(s[i]));
    }
    for(int i =0;i<5;i++) //generate rocket
    {
        r[i] = new rocket;
        r[i]->setPos(-500,0);
        r[i]->setPixmap(QPixmap(":/rocket").scaledToHeight(80));
        r[i]->connect(this,SIGNAL(spring_move(float)),r[i],SLOT(move(float)));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(r[i]));
    }

    scene->addItem(player);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::jump()
{
    dy+=0.1;
    y+=dy;
    if(flying_height<=3000)
    {
        dy = -4;
        flying_height-=dy;
    }
    if (y>800){
        end->set_score(score);
        end->show();
        timer->stop();
        hide();
    }
    for(int i =0;i<20;i++)
    if(dy>0 &&player->y()+100<plat[i]->plat->y()
            &&player->y()+100+dy>=plat[i]->plat->y()
            &&player->x()>=plat[i]->plat->x()-80
            &&player->x()<=plat[i]->plat->x()+80)
    {
        player->setPos(x,plat[i]->plat->y());
        dy = -8;
    }
    for(int i =0;i<2;i++)
    if(dy>0 &&player->y()+100<m[i]->y()
            &&player->y()+100+dy>=m[i]->y()
            &&player->x()>=m[i]->x()-80
            &&player->x()<=m[i]->x()+80)
    {
        dy = -12;
        m[i]->setPos(-600,0);
    }
    for(int i =0;i<5;i++)
    if(dy>0 &&player->y()+100<s[i]->y()
            &&player->y()+100+dy>=s[i]->y()
            &&player->x()>=s[i]->x()-80
            &&player->x()<=s[i]->x()+80)
    {
        player->setPos(x,plat[i]->plat->y());
        dy = -16;
        s[i]->setPixmap(QPixmap(":/after").scaledToWidth(20));
    }

    if (y<350){
        y = 350;
        player->setPos(x,y);
        for(int i =0;i<20;i++)
        plat[i]->plat->setY(plat[i]->plat->y()-dy);
        emit monster_move(dy);
        emit spring_move(dy);
        score+=dy;
    }
    else {
        player->setPos(x,y);
    }
    ui->label->setNum(-score);
}
void MainWindow::move()
{
    for(int i=0;i<20;i++)
        plat[i]->move();
    if(x<-50)
    {
        x+=600;
        player->setPos(x,y);
    }
    if(x>550)
    {
        x-=600;
        player->setPos(x,y);
    }
    if(is_moving_left==true)
    {
        x+=dx;
        player->setPos(x,y);
        return;
    }
    if(is_moving_right==true)
    {
        x+=dx;
        player->setPos(x,y);
        return;
    }
    if(dx>0)
        {
            if(dx-0.5<0)
                return;
            else{
                dx-=0.5;
                x+=dx;
            }
        }
        if(dx<0)
        {
            if(dx+0.5>0)
                return;
            else
            {
                dx+=0.5;
                x+=dx;
            }
        }
        player->setPos(x,y);
}
void MainWindow::set_platform()
{
    if(plat[k]->plat->y()>800)
    {
        if(k == 0)
        {
            delete plat[k];
            if(rand()%2==0)
            {
                plat[k] = new form1;
                plat[k]->set_pixmap(rand()%500,plat[19]->plat->y()-(rand()%200)-30);
                if(rand()%10==0)
                {
                    if(rand()%2==1)
                    {
                        if(spring_number==5)
                        spring_number = 0;
                        s[spring_number]->setPixmap(QPixmap(":/before").scaled(20,20));
                        s[spring_number]->setPos(plat[k]->plat->x()+40,plat[k]->plat->y()-20);
                        spring_number++;
                    }
                    else
                    {
                        if(rocket_number==5)
                        rocket_number = 0;
                        r[rocket_number]->setPixmap(QPixmap(":/rocket").scaledToHeight(60));
                        r[rocket_number]->setPos(plat[k]->plat->x()+40,plat[k]->plat->y()-60);
                        rocket_number++;
                    }
                }
            }
            else
            {
                plat[k] = new form2;
                plat[k]->set_pixmap(rand()%500,plat[19]->plat->y()-(rand()%200)-30);
            }
            plat[k]->plat->setZValue(-1);
            scene->addItem(plat[k]->plat);
            k+=1;
        }
        else
        {
            delete plat[k];
            if(rand()%3==0)
            {
                plat[k] = new form2;
                plat[k]->set_pixmap(rand()%500,plat[k-1]->plat->y()-(rand()%200)-30);
            }
            else
            {
                plat[k] = new form1;
                plat[k]->set_pixmap(rand()%500,plat[k-1]->plat->y()-(rand()%200)-30);
                if(rand()%10==0)
                {
                    if(rand()%2==0)
                    {
                        if(spring_number==5)
                        spring_number = 0;
                        s[spring_number]->setPixmap(QPixmap(":/before").scaled(20,20));
                        s[spring_number]->setPos(plat[k]->plat->x()+40,plat[k]->plat->y()-20);
                        spring_number++;
                    }
                    else
                    {
                        if(rocket_number==5)
                        rocket_number = 0;
                        r[rocket_number]->setPixmap(QPixmap(":/rocket").scaledToHeight(60));
                        r[rocket_number]->setPos(plat[k]->plat->x()+40,plat[k]->plat->y()-60);
                        rocket_number++;
                    }
                }
            }
            plat[k]->plat->setZValue(-1);
            scene->addItem(plat[k]->plat);
            k+=1;
            if(k==20)
                k=0;
        }
    }
}
void MainWindow::set_hazard()
{
    if(score/(3000)<count)
    {
        if(monster_count==2)
            monster_count=0;
        if(blackhole_count==2)
            blackhole_count = 0;
        bool if_collide = true;
        count--;
        if(rand()%5==0)
        {
            while(1)
            {
                if_collide = false;
                h[blackhole_count]->setPos(rand()%500,player->y()-1600);
                for(int i =0;i<20;i++)
                    if_collide =h[blackhole_count]->collidesWithItem(plat[i]->plat);
                if(if_collide)
                    continue;
                else
                {
                    blackhole_count++;
                    break;
                }
             }
        }
        else
        {
            while(1)
            {
                if_collide = false;
                m[monster_count]->setPos(rand()%500,player->y()-1600);
                m[monster_count]->set_start(m[monster_count]->x(),m[monster_count]->y());
                for(int i =0;i<20;i++)
                    if_collide =m[monster_count]->collidesWithItem(plat[i]->plat);
                if(if_collide)
                    continue;
                else
                {
                    monster_count++;
                    break;
                }
             }
        }
    }
}
void MainWindow::if_collide()
{
    for(int i=0;i<bullet_nember;i++)
        for(int j=0;j<2;j++)
            if(b[i]->collidesWithItem(m[j]))
            {
                b[i]->setPos(-800,0);
                m[j]->setPos(-600,0);
            }
    for(int i =0;i<5;i++)
        if(player->collidesWithItem(r[i]))
        {
            flying_height = 0;
            r[i]->setPos(-500,0);
        }
    for(int i=0;i<2;i++)
        if(player->collidesWithItem(h[i]))
        {
            end->set_score(score);
            end->show();
            timer->stop();
            hide();
        }
    for(int i=0;i<2;i++)
        if(player->collidesWithItem(m[i]))
        {
            end->set_score(score);
            end->show();
            timer->stop();
            hide();
        }
}
void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()){
    case Qt::Key_D :
    {
        is_moving_right = true;
        QPixmap pic(":/icedoodle");
        player->setPixmap(pic.scaledToHeight(100).transformed(QTransform().scale(-1, 1)));
        transformed = true;
        dx = 3;
    }
    break;
    case Qt::Key_A :
    {
        is_moving_left = true;
        QPixmap pic(":/icedoodle");
        player->setPixmap(pic.scaledToHeight(100));
        transformed = false;
        dx = -3;
    }
    break;
    case Qt::Key_Space:
    {
        if(bullet_count==30)
            bullet_count = 0;
        player->setPixmap(QPixmap(":/shooting").scaled(100,100));
        b[bullet_count]->setPos(player->x()+43.5,player->y()+15);
        bullet_count++;
    }
        break;
    }
}\
void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
    switch (e->key()){
    case Qt::Key_D :
    {
        is_moving_right = false;
    }
    break;
    case Qt::Key_A :
    {
        is_moving_left = false;
    }
    break;
    case Qt::Key_Space:
    {
        QPixmap pic(":/icedoodle");
        if(transformed)
        player->setPixmap(pic.scaledToHeight(100).transformed(QTransform().scale(-1, 1)));
        else
        player->setPixmap(pic.scaledToHeight(100));
    }
        break;
    }
}
void MainWindow::on_pushButton_clicked()
{
    if(!paused)
    {
        paused = true;
        timer->stop();
        return;
    }
    if(paused)
    {
        paused = false;
        timer->start(8);
        return;
    }
}
