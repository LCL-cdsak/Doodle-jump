#ifndef MENU_H
#define MENU_H

#include <QDialog>
#include "mainwindow.h"
namespace Ui {
class menu;
}

class menu : public QDialog
{
    Q_OBJECT

public:
    explicit menu(QWidget *parent = nullptr);
    ~menu();
    bool play = true;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::menu *ui;
    MainWindow *map;
};

#endif // MENU_H
