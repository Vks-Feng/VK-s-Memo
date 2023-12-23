#include "login.h"
#include "widget.h"
#include "notice.h"
#include "ui_login.h"
#include "wrong.h"
#include "user.h"
User user;

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
}

Login::~Login()
{
    delete ui;
}

bool Login::ConfirmUser(QString ID, QString Password)
{
    QFile idfile(ID + "passwordfile");
    idfile.open(QIODevice::ReadWrite);
    if(!idfile.atEnd())
    {
        if(Password == QString(idfile.readAll()))
        {
            idfile.close();
            return true;
        }
        else
        {
            idfile.close();//只有在密码错误时返回false
            return false;
        }
    }
    else
    {
        idfile.write(Password.toUtf8());
        idfile.close();
        return true;
    }
}

void Login::on_btn_login_clicked()
{
    if(!ui->IDinput->text().isEmpty()&&!ui->Passwordinput->text().isEmpty())
    {
        if(ConfirmUser(ui->IDinput->text(),ui->Passwordinput->text()))
        {
            User in(ui->IDinput->text(),ui->Passwordinput->text());
            user = in;
            Widget* w = new Widget;
            w->show();
            this->close();
        }
        else
        {
            Wrong* wrong = new Wrong;
            wrong->show();
        }
    }
    else
    {
        Notice* notice = new Notice;
        notice->show();
    }

}

