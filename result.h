#ifndef RESULT_H
#define RESULT_H

#include <QDialog>

namespace Ui {
class result;
}

class result : public QDialog
{
    Q_OBJECT

public:
    explicit result(QWidget *parent = nullptr);
    ~result();
     void set_score(float x);
private:
    Ui::result *ui;
    int final_score = 0;
};

#endif // RESULT_H
