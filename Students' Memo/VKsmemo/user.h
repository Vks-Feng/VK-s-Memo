#ifndef USER_H
#define USER_H
#include <QString>
#include <QFile>
class User
{
public:
    User();
    User(QString ID, QString Password);
    void SetUserCoursenums();
    int GetUserCoursenums();
    void ChangeUserCoursenums(QString num);
    void SetUserColor();
    QString GetUserColor();
    void ChangeUserColor(QString color);
    QString GetFilenamecs();
    QString GetFilenamehw();
    QString GetFilenamerm();
private:
    QString ID_;
    QString Password_;
    int num_;
    QString color_;
    QString NUMfile;
    QString COLORfile;
    QString Filenamecs;
    QString Filenamehw;
    QString Filenamerm;
};

#endif // USER_H
