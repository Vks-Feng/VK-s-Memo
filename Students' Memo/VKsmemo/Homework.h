#ifndef HOMEWORK_H
#define HOMEWORK_H

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <QWidget>
#include <QDataStream>
#include "MemoInfo.hpp"


using namespace std;

struct Nodehw;

//-------------------------------------作业类--------------------------------------
class Homework : public MemoInfo<Nodehw,Homework>
{
public:
    friend QDataStream& operator <<(QDataStream &out,Homework &add);//将新增作业输出
    friend QDataStream& operator >>(QDataStream &in,Homework &read);//将信息读入
    Homework(QString name = "nth", QString content = "nth", QString level = "unknown", QString finish = "未完成", QString submission = "unknown", int year = 0, int month = 0, int date = 0, int hour = 0, int min = 0)
    {
        name_ = name;
        content_ = content;
        level_ = level;
        submission_ = submission;
        finish_ = finish;
        this->SetYear(year);
        this->SetMonth(month);
        this->SetDate(date);
        this->SetHour(hour);
        this->SetMin(min);
    }
    //设置接口
    void SetName(QString name);
    void SetContent(QString content);
    void SetLevel(QString level);
    void SetSubmission(QString submission);
    void SetFinish(QString finish);
    //获取接口
    QString GetName();
    QString GetContent();
    QString GetLevel();
    QString GetFinish();
    QString GetSubmission();
    bool GetMumber();
    void Save(Nodehw* const node);
    Nodehw* Fetch();
    void Delete(const int n);
private:
    QString name_;//哪一节课的作业
    QString content_;//作业内容
    QString level_;//重要程度
    QString finish_;
    QString submission_;

};
//用于存储作业的链表节点
struct Nodehw
{
    Homework val;
    Nodehw* next;
};

//运算符重载

QDataStream& operator <<(QDataStream &out,Nodehw &t);
QDataStream& operator >>(QDataStream &in,Nodehw &n);

#endif // HOMEWORK_H
