#include "Homework.h"
#include <QDebug>
#include <QDataStream>
#include <QFile>
#include "widget.h"
#include "fix.h"
#include "user.h"
extern User user;
//运算符重载部分
QDataStream& operator <<(QDataStream &out,Homework &add)//输出新增
{
    out<<add.name_<<add.content_<<add.level_<<add.finish_<<add.submission_<<add.GetYear()
        <<add.GetMonth()<<add.GetDate()<<add.GetHour()<<add.GetMin();
    return out;
}

QDataStream& operator >>(QDataStream &in,Homework &n)//读入数据
{
    int year;
    int month;
    int date;
    int hour;
    int min;
    in >> n.name_ >> n.content_ >> n.level_ >> n.finish_ >> n.submission_
        >> year >> month >> date >> hour >> min;
    n.SetYear(year);
    n.SetMonth(month);
    n.SetDate(date);
    n.SetHour(hour);
    n.SetMin(min);
    return in;
}

QDataStream& operator <<(QDataStream &out,Nodehw* &t)
{
    out << t->val;
    return out;
}

QDataStream& operator >>(QDataStream &in,Nodehw* &n)
{
    in >> n->val;
    return in;
}

//作业类的接口
void Homework::SetSubmission(QString submission)
{
    submission_ = submission;
}

void Homework::SetName(QString name)
{
    name_ = name;
}

void Homework::SetLevel(QString level)
{
    level_ = level;
}

void Homework::SetContent(QString content)
{
    content_ = content;
}

void Homework::SetFinish(QString finish)
{
    finish_ = finish;
}

QString Homework::GetName()
{
    return name_;
}

QString Homework::GetLevel()
{
    return level_;
}

QString Homework::GetFinish()
{
    return finish_;
}

QString Homework:: GetSubmission()
{
    return submission_;
}

QString Homework::GetContent()
{
    return content_;
}

//---------------------保存模块----------------------

//保存模块
void Homework::Save(Nodehw* const pNew)
{
    Nodehw* pointer = NULL;
    Nodehw* pHead = NULL;
    Nodehw* Each = new Nodehw;
    Each->next = NULL;
    int i = 0;
    QFile file(user.GetFilenamehw());
    file.open(QFile::ReadOnly);
    QDataStream fout(&file);
    while (!fout.atEnd())
    {
        fout>>Each;
        if (i == 0)
        {
            pHead = Each;
            pointer = pHead;
        }
        else if (i > 0)
        {
            pointer->next = Each;
            pointer = Each;
        }
        i++;
        Each = new Nodehw;
        Each->next = NULL;
    }
    delete Each;
    if (pNew)
    {
        pointer = pNew;
        int range = 0;
        while (pointer)
        {
            range++;
            pointer = pointer->next;
        }
        pointer = pNew;
    }
    else if (!pNew)
    {
        return ;
    }
    pointer->next= pHead;
    Nodehw* Np = pNew;
    file.close();
    if (!file.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {
        qDebug() << "fail to open hwfile";
    }
    QDataStream fin(&file);
    i = 1;
    while (Np)
    {

        fin<<Np;
        Np = Np->next;
        i++;
    }
    file.close();
}

Nodehw* Homework::Fetch(void)
{
    QFile file(user.GetFilenamehw());;
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "homeworkfetch";
    }
    QDataStream fout(&file);
    if (fout.atEnd())//防止用户初次使用时文件为空导致返回空指针
    {
        QString name = "CrazyThu";
        QString content = "V Vkun_s 50";
        QString level = "重要";
        QString finish = "未完成";
        QString submission = "微信红包";
        int year = 9999;
        int month = 9;
        int date = 9;
        int hour = 9;
        int min = 9;
        Homework* Initial = new Homework(name,content,level,finish,submission,year,month,date,hour,min);
        Nodehw* Initialnode = new Nodehw;
        Initialnode->val = *Initial;
        Initialnode->next = NULL;
        return Initialnode;
    }
    Nodehw* pHead = NULL;
    Nodehw* Each = new Nodehw;
    Each->next = NULL;
    int i = 0;
    Nodehw* pointer = NULL;
    while (!fout.atEnd())
    {
        fout>>Each;
        if (i == 0)
        {
            pHead = Each;
            pointer = pHead;
        }
        else if (i > 0)
        {
            pointer->next = Each;
            pointer = Each;
        }
        i++;
        Each = new Nodehw;
        Each->next = NULL;
    }
    delete Each;
    return pHead;
}

void Homework::Delete(const int n)
{
    Nodehw* Head = Arrange(Fetch());
    Nodehw* current = Head;
    if(n == 1)
    {
        Head = Head->next;
    }
    else if(n > 1)
    {
        int i = 0;
        while(current)
        {
            i++;
            if(i == n-1)
            {
                if(current->next)
                {
                    current->next = current->next->next;
                }
            }
            current = current->next;
        }
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

