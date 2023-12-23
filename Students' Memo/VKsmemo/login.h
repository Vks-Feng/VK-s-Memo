#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>


namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    bool ConfirmUser(QString ID, QString Password);
private slots:
    void on_btn_login_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
