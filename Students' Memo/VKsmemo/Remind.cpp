#include <QDebug>
#include <QDataStream>
#include <QFile>
#include "Remind.h"
#include "user.h"
extern User user;
//------------------------------运算符重载部分------------------------------
QDataStream& operator <<(QDataStream &out,Remind &add)//输出新增
{
    out << add.organizer_<<add.accontent_<<add.GetYear()<<add.GetMonth()<<add.GetDate()
        <<add.GetHour()<<add.GetMin();
    return out;
}

QDataStream& operator >>(QDataStream &in,Remind &n)//读入数据
{
    int year;
    int month;
    int date;
    int hour;
    int min;
    in >> n.organizer_ >> n.accontent_ >> year >> month >> date >> hour >> min;
    n.SetYear(year);
    n.SetMonth(month);
    n.SetDate(date);
    n.SetHour(hour);
    n.SetMin(min);
    return in;
}

QDataStream& operator <<(QDataStream &out,Noderm* &t)
{
    out << t->val;
    return out;
}

QDataStream& operator >>(QDataStream &in,Noderm* &n)
{
    in >> n->val;
    return in;
}

//----------------------接口部分----------------------
void Remind::SetOrganizer(QString orginazer)
{
    organizer_ = orginazer;
}

void Remind::SetAcConnent(QString accontent)
{
    accontent_ = accontent;
}

QString Remind::GetOrganizer()
{
    return organizer_;
}

QString Remind::GetAcContent()
{
    return accontent_;
}

//--------------------------service------------------------
void Remind::Save(Noderm* const pNew)
{
    Noderm* pointer = NULL;
    Noderm* pHead = NULL;
    Noderm* Each = new Noderm;
    Each->next = NULL;
    int i = 0;
    QFile file(user.GetFilenamerm());
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
        Each = new Noderm;
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
    Noderm* Np = pNew;
    file.close();
    if (!file.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {
        qDebug() << "fail to open rmfile";
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

Noderm* Remind::Fetch(void)
{
    QFile file(user.GetFilenamerm());
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"why fail to open refile ";
    }
    QDataStream fout(&file);
    if (fout.atEnd())//防止用户初次使用时文件为空导致返回空指针
    {
        QString organizer = "Vkun_s";
        QString accontent = "v Vkun_s 50";
        int year = 9999;
        int month = 9;
        int date = 9;
        int hour = 9;
        int min = 9;
        Remind* Initial = new Remind(organizer, accontent, year, month, date, hour, min);
        Noderm* Initialnode = new Noderm;
        Initialnode->val = *Initial;
        Initialnode->next = NULL;
        return Initialnode;
        return NULL;
    }
    Noderm* pHead = NULL;
    Noderm* Each = new Noderm;
    Each->next = NULL;
    int i = 0;
    Noderm* pointer = NULL;
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
        Each = new Noderm;
        Each->next = NULL;
    }
    delete Each;
    return pHead;
}

void Remind::Delete(const int n)
{
    Noderm* Head = Arrange(Fetch());
    Noderm* current = Head;
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
    QFile file(user.GetFilenamerm());
    if(!file.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {
        qDebug()<<"failed to open rmfile";
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
