#include "fixcs.h"
#include "ui_fixcs.h"
#include "Course.h"
#include "notice.h"
#include "user.h"
#include <QRegularExpressionValidator>
extern User user;
fixcs::fixcs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fixcs)
{
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());
    ui->deletecsX->setValidator(new QRegularExpressionValidator(QRegularExpression("[1-7]{1}")));
    ui->deletecsY1->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]{2}")));
    ui->deletecsY2->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]{2}")));
}

fixcs::~fixcs()
{
    delete ui;
}

void fixcs::on_confirmcsdelete_clicked()
{
    if((!ui->deletecsname->text().isEmpty())&&(!ui->deletecsX->text().isEmpty())
        &&(!ui->deletecsY1->text().isEmpty())&&(!ui->deletecsY2->text().isEmpty()))
    {
        QString name = ui->deletecsname->text() ;
        int x = ui->deletecsX->text().toInt();
        int y1 = ui->deletecsY1->text().toInt();
        int y2 = ui->deletecsY2->text().toInt();
        Course manage;
        manage.CourseDelete(name, x, y1, y2);
        this->close();
    }
    else
    {
        Notice* notice = new Notice;
        notice->show();
    }
}

