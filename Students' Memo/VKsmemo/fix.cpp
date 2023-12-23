#include "fix.h"
#include "ui_fix.h"
#include "Homework.h"
#include "widget.h"
#include "notice.h"
#include "user.h"
#include <QDebug>
#include <QDataStream>
#include <QFile>
extern User user;
Fix::Fix(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Fix)
{
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());
    ui->change->hide();
}

Fix::~Fix()
{
    delete ui;
}
//点取消可以关闭窗口
void Fix::on_cancel_2_clicked()
{
    this->close();
}

//实现修改时填内容，删除时忽略
void Fix::on_radio_deletehw_clicked()
{
    ui->change->hide();
}

void Fix::on_radio_changehw_clicked()
{
    ui->change->show();
}

//点击确定按钮
void Fix::on_confirm_2_clicked()
{
    Homework manage;
    if(ui->radio_deletehw->isChecked()&&(!ui->hw_number->text().isEmpty()))
    {
        manage.Delete(ui->hw_number->text().toInt());
        this->close();
    }
    else if(ui->radio_changehw->isChecked()&&(!ui->hw_number->text().isEmpty())
             &&(!ui->changehwcontent->text().isEmpty())&&(!ui->changehwname->text().isEmpty()))
    {
        ChangeHomework(ui->hw_number->text().toInt());
        this->close();
    }
    else
    {
        Notice* notice = new Notice;
        notice->show();
    }

}

void Fix::ChangeHomework(int n)
{
    Homework manage;
    Nodehw* Head = manage.Arrange(manage.Fetch());
    Nodehw* current = Head;
    int i = 0;
    while(current)
    {
        i++;
        if(i == n)
        {
            current->val.SetName(ui->changehwname->text());
            current->val.SetContent(ui->changehwcontent->text());
            current->val.SetSubmission(ui->changehwsubmission->text());
            current->val.SetYear(ui->changehwtime->date().year());
            current->val.SetMonth(ui->changehwtime->date().month());
            current->val.SetDate(ui->changehwtime->date().day());
            current->val.SetHour(ui->changehwtime->time().hour());
            current->val.SetMin(ui->changehwtime->time().minute());
            if(ui->changehwlevel1->isChecked())
            {
                current->val.SetLevel("重要");
            }
            else if(ui->changehwlevel2->isChecked())
            {
                current->val.SetLevel("一般");
            }
            else if(ui->changehwlevel3->isChecked())
            {
                current->val.SetLevel("不重要");
            }
            if(ui->changehwstatus1->isChecked())
            {
                current->val.SetFinish("已完成");
            }
            else if(ui->changehwstatus1_2->isChecked())
            {
                current->val.SetFinish("未完成");
            }
        }
        current = current->next;
    }
    QFile file(user.GetFilenamehw());
    if(!file.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {
        qDebug()<<"failed to open hwfile";
    }
    QDataStream fin(&file);
    current = Head;
    while(current)
    {
        fin<<current->val;
        current = current->next;
    }
    file.close();
}
