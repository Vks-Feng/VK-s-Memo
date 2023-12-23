#include "fixre.h"
#include "ui_fixre.h"
#include "Remind.h"
#include "widget.h"
#include "notice.h"
#include "user.h"
#include <QFile>
#include <QDataStream>
extern User user;
FixRE::FixRE(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FixRE)
{
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());
    ui->change_ac->hide();
}

FixRE::~FixRE()
{
    delete ui;
}

//实现修改时填内容，删除时忽略
void FixRE::on_btn_ac_change_clicked()
{
    ui->change_ac->show();
}

void FixRE::on_btn_ac_delete_clicked()
{
    ui->change_ac->hide();
}

//点取消关闭窗口
void FixRE::on_cancel_ac_clicked()
{
    this->close();
}

void FixRE::on_confirm_ac_clicked()
{
    Remind manage;
    if(ui->btn_ac_delete->isChecked()&&(!ui->rm_num->text().isEmpty()))
    {
        manage.Delete(ui->rm_num->text().toInt());
        this->close();
    }
    else if(ui->btn_ac_change->isChecked()&&(!ui->changeACcon->text().isEmpty()))
    {
        ChangeRemind(ui->rm_num->text().toInt());
        this->close();
    }
    else
    {
        Notice* notice = new Notice;
        notice->show();
    }
}

void FixRE::ChangeRemind(int n)
{
    Remind manage;
    Noderm* Head = manage.Arrange(manage.Fetch());
    Noderm* current = Head;
    int i = 0;
    while(current)
    {
        i++;
        if(i == n)
        {
            current->val.SetOrganizer(ui->changeAAorga->text());
            current->val.SetAcConnent(ui->changeACcon->text());
            current->val.SetYear(ui->changeActime->date().year());
            current->val.SetMonth(ui->changeActime->date().month());
            current->val.SetDate(ui->changeActime->date().day());
            current->val.SetHour(ui->changeActime->time().hour());
            current->val.SetMin(ui->changeActime->time().minute());
        }
        current = current->next;
    }
    QFile file(user.GetFilenamerm());
    if(!file.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {
        qDebug()<<"failed to open remind file";
    }
    QDataStream fin(&file);
    current = Head;
    while(current)
    {
        fin << current;
        current = current->next;
    }
    file.close();
}
