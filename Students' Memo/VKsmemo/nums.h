#ifndef NUMS_H
#define NUMS_H

#include <QWidget>

namespace Ui {
class Nums;
}

class Nums : public QWidget
{
    Q_OBJECT

public:
    explicit Nums(QWidget *parent = nullptr);
    ~Nums();

private:
    Ui::Nums *ui;
};

#endif // NUMS_H
