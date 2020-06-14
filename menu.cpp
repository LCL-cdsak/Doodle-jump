#include "menu.h"
#include "ui_menu.h"

menu::menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);
    this->setWindowTitle("DOODLE JUMP!");
    map = new MainWindow;
    this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
                QBrush(QPixmap(":/menu").scaled(// 縮放背景圖.
                    this->size(),
                    Qt::IgnoreAspectRatio,
                    Qt::SmoothTransformation)));             // 使用平滑的縮放方式
        this->setPalette(palette);
}

menu::~menu()
{
    delete ui;
}

void menu::on_pushButton_clicked()
{
    map->show();
    hide();
}

void menu::on_pushButton_2_clicked()
{
    exit(1);
}
