#include "result.h"
#include "ui_result.h"

result::result(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::result)
{
    ui->setupUi(this);
    this->setWindowTitle("DOODLE JUMP!");
}

result::~result()
{
    delete ui;
}

void result::set_score(float x)
{
    final_score = x;
    ui->label_3->setNum(-final_score);
}
