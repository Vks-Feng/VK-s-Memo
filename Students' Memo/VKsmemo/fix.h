#ifndef FIX_H
#define FIX_H

#include <QWidget>

namespace Ui {
class Fix;
}

class Fix : public QWidget
{
    Q_OBJECT
    friend void ChangeHomework(int n);
public:
    explicit Fix(QWidget *parent = nullptr);
    ~Fix();

private slots:

    void on_cancel_2_clicked();

    void on_radio_deletehw_clicked();

    void on_radio_changehw_clicked();

    void on_confirm_2_clicked();

    void ChangeHomework(int n);

private:
    Ui::Fix *ui;
};



#endif // FIX_H
