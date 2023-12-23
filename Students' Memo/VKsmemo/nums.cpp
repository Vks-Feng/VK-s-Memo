#include "nums.h"
#include "ui_nums.h"

Nums::Nums(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Nums)
{
    ui->setupUi(this);
}

Nums::~Nums()
{
    delete ui;
}
