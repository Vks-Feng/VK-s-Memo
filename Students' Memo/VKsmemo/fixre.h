#ifndef FIXRE_H
#define FIXRE_H

#include <QWidget>

namespace Ui {
class FixRE;
}

class FixRE : public QWidget
{
    Q_OBJECT

public:
    explicit FixRE(QWidget *parent = nullptr);
    ~FixRE();

private slots:
    void on_btn_ac_change_clicked();

    void on_btn_ac_delete_clicked();

    void on_cancel_ac_clicked();

    void on_confirm_ac_clicked();

    void ChangeRemind(int n);

private:
    Ui::FixRE *ui;
};

#endif // FIXRE_H
