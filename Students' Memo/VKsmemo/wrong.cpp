#include "wrong.h"
#include "ui_wrong.h"

Wrong::Wrong(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Wrong)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
}

Wrong::~Wrong()
{
    delete ui;
}
