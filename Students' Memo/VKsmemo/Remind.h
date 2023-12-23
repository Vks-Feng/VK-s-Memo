#ifndef REMIND_H
#define REMIND_H

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <QWidget>
#include <QDataStream>
#include "MemoInfo.hpp"

using namespace std;

struct Noderm;

class Remind : public MemoInfo<Noderm,Remind>
{
public:
    friend QDataStream& operator <<(QDataStream &out,Remind &add);//将新增作业输出
    friend QDataStream& operator >>(QDataStream &in,Remind &read);//将信息读入
    //------------constructor------------
    Remind(QString orginazer = "unknown", QString accontent = "unknown", int year = 0, int month = 0, int date = 0, int hour = 0, int min = 0)
    {
        organizer_ = orginazer;
        accontent_ = accontent;
        this->SetYear(year);
        this->SetMonth(month);
        this->SetDate(date);
        this->SetHour(hour);
        this->SetMin(min);
    }
    //----------------写入---------------
    void SetOrganizer(QString orginazer);
    void SetAcConnent(QString acconnent);
    //----------------读取---------------
    QString GetOrganizer();
    QString GetAcContent();
    bool GetMumber();
    void Save(Noderm* const node);
    Noderm* Fetch();
    void Delete(const int n);
private:
    QString organizer_;
    QString accontent_;

};

struct Noderm
{
    Remind val;
    Noderm* next;
};

//运算符重载
QDataStream& operator <<(QDataStream &out,Noderm &t);
QDataStream& operator >>(QDataStream &in,Noderm &n);

#endif // REMIND_H
