#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "QObject"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <platform.h>
#include <form1.h>
#include <form2.h>
#include <bullet.h>
#include <monster.h>
#include <spring.h>
#include <rocket.h>
#include <result.h>
#include <blackhole.h>
#define bullet_nember 30
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void monster_move(float dy);
    void spring_move(float dy);
public slots:
    void jump();
    void move();
    void set_platform();
    void set_hazard();
    void if_collide();
protected:
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
private slots:
    void on_pushButton_clicked();
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *player;
    float x=0,y=0;
    float dx=0,dy=0;
    bool is_moving_left=false, is_moving_right=false,paused = false,transformed;
    platform *plat[20];
    int k=0,score=0,temp = 0,count=0,monster_count = 0,bullet_count = 0,spring_number = 0,rocket_number =0,blackhole_count = 0;
    Monster *m[2];
    QTimer *timer,*timer2;
    bullet *b[bullet_nember];
    spring *s[5];
    rocket *r[5];
    blackhole *h[2];
    int flying_height = 4000;
    result *end;
};

#endif // MAINWINDOW_H
