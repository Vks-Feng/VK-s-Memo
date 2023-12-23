#include "user.h"
#include <QDebug>

User::User()
{

}

User::User(QString ID, QString Password)
{
    this->ID_ = ID;
    this->Password_ = Password;
    this->COLORfile = ID + "colorF";
    this->NUMfile = ID + "numF";
    this->Filenamecs = ID + "courseF.dat";
    this->Filenamehw = ID + "homeworkF.dat";
    this->Filenamerm = ID + "remindF.dat";
    this->SetUserColor();
    this->SetUserCoursenums();
}

void User::SetUserColor()
{
    QString color;
    QFile file(COLORfile);
    file.open(QIODevice::ReadOnly);
    if(file.atEnd())
    {
        color = "rgb(245, 190, 197)";
    }
    else
    {
        color = QString(file.readAll());
    }
    file.close();
    this->color_ = color;
}

void User::ChangeUserColor(QString color)
{
    qDebug() << "hh:" << COLORfile;
    QFile file(COLORfile);
    file.open(QIODevice::WriteOnly|QIODevice::Truncate);
    file.write(color.toUtf8());
    file.close();
    this->color_ = color;
}

QString User::GetUserColor()
{
    return color_;
}

void User::SetUserCoursenums()
{
    QFile file(NUMfile);
    file.open(QIODevice::ReadOnly);
    if(file.atEnd())
    {
        this->num_ = 13;
    }
    else
    {
        int num;
        QByteArray array = file.readAll();
        num = array.toInt();
        this->num_ = num;
    }
}

void User::ChangeUserCoursenums(QString num)
{
    QFile file(NUMfile);
    file.open(QIODevice::WriteOnly|QIODevice::Truncate);
    file.write(num.toUtf8());
    file.close();
    this->num_ = num.toInt();
}

int User::GetUserCoursenums()
{
    return this->num_;
}

QString User::GetFilenamecs()
{
    return Filenamecs;
}
QString User::GetFilenamehw()
{
    return Filenamehw;
}
QString User::GetFilenamerm()
{
    return Filenamerm;
}


