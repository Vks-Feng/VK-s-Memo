#ifndef FIXCS_H
#define FIXCS_H

#include <QWidget>


namespace Ui {
class fixcs;
}

class fixcs : public QWidget
{
    Q_OBJECT

public:
    explicit fixcs(QWidget *parent = nullptr);
    ~fixcs();

private slots:
    void on_confirmcsdelete_clicked();

private:
    Ui::fixcs *ui;
};

#endif // FIXCS_H
