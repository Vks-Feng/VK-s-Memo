#include "Course.h"
#include <QDebug>
#include <QDataStream>
#include <QFile>
#include "wrong.h"
#include "login.h"
#include "user.h"
extern User user;
//运算符重载部分
QDataStream& operator <<(QDataStream &out,Course &add)//输出新增
{
    out << add._x << add._y1 << add._y2 << add._score << add._classname << add._classroom << add._teacher << add._note;
    return out;
}

QDataStream& operator >>(QDataStream &in,Course &n)//读入数据
{
    in >> n._x >> n._y1 >> n._y2 >> n._score >> n._classname >> n._classroom >> n._teacher >> n._note;
    return in;
}

QDataStream& operator <<(QDataStream &out,Nodecs* &t)
{
    out << t->val;
    return out;
}

QDataStream& operator >>(QDataStream &in,Nodecs* &n)
{
    in >> n->val;
    return in;
}

QString Course::GetName()
{
    return _classname;
}

QString Course::GetRoom()
{
    return _classroom;
}

QString Course::GetTeach()
{
    return _teacher;
}

QString Course::GetNote()
{
    return _note;
}

int Course::GetScore()
{
    return _score;
}

int Course::GetX()
{
    return _x;
}

int Course::GetY1()
{
    return _y1;
}

int Course::GetY2()
{
    return _y2;
}


void Course::SetName(QString classname)
{
    _classname = classname;
}

void Course::SetRoom(QString classroom)
{
    _classroom = classroom;
}

void Course::SetTeach(QString teacher)
{
    _teacher = teacher;
}

void Course::SetNote(QString note)
{
    _note = note;
}

void Course::SetScore(int score)
{
    _score = score;
}

void Course::SetX(int x)
{
    _x = x;
}

void Course::SetY1(int y1)
{
    _y1 = y1;
}

void Course::SetY2(int y2)
{
    _y2 = y2;
}

void Course::SaveCourse(Nodecs* const pNew)
{
    Nodecs* pointer = NULL;
    Nodecs* pHead = NULL;
    Nodecs* Each = new Nodecs;
    Each->next = NULL;
    int i = 0;
    QFile file(user.GetFilenamecs());
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
        Each = new Nodecs;
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
    Nodecs* Np = pNew;
    file.close();
    if (!file.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {
        qDebug() << "failed to open cs file";
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

Nodecs* Course::CourseFetch()
{
    QFile file(user.GetFilenamecs());
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "coursefetch";
    }
    QDataStream fout(&file);
    if (fout.atEnd())
    {
        return NULL;
    }
    Nodecs* pHead = NULL;
    Nodecs* Each = new Nodecs;
    Each->next = NULL;
    int i = 0;
    Nodecs* pointer = NULL;
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
        Each = new Nodecs;
        Each->next = NULL;
    }
    delete Each;
    return pHead;
}

Nodecs* Course::CourseSearch(QString name)
{
    Nodecs* Head = this->CourseFetch();
    Nodecs* current = Head;
    while(current)
    {
        if(current->val.GetName() == name)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void Course::CourseDelete(QString name, int x, int y1, int y2)
{
    Nodecs* Head = this->CourseFetch();
    Nodecs* current = Head;
    int i = 0;
    while(current)
    {
        ++i;
        if(i == 1 && current->val.GetName() == name && current->val.GetX() == x
            && current->val.GetY1() == y1 && current->val.GetY2() == y2)
        {
            Head = current->next;
        }
        else if(current->next &&current->next->val.GetName() == name && current->next->val.GetX() == x
                   && current->next->val.GetY1() == y1 && current->next->val.GetY2() == y2)
        {
            current = current->next->next;
        }
        current = current->next;
    }
    QFile file(user.GetFilenamecs());
    if(!file.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {
        qDebug()<<"failed to open csfile";
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

void Course::CourseDelete(int nums)
{
    Nodecs* Head = this->CourseFetch();
    Nodecs* current = Head;
    int i = 0;
    while(current)
    {
        i++;
        if(i == 1 && current->val.GetY2()>nums)
        {
            Head = current->next;
        }
        else if(current->next && current->next->val.GetY2()>nums)
        {
            current = current->next->next;
        }
        current = current->next;
    }

    QFile file(user.GetFilenamecs());
    if(!file.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {
        qDebug()<<"failed to open csfile";
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


