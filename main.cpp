#include "mainwindow.h"
#include <QApplication>
#include <QMainWindow>
#include "menu.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    menu w;
    w.show();
    return a.exec();
}
