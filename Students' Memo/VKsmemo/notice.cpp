#include "notice.h"
#include "ui_notice.h"

Notice::Notice(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Notice)
{
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());
}

Notice::~Notice()
{
    delete ui;
}

void Notice::on_noticecon_clicked()
{
    this->close();
}

