#ifndef WRONG_H
#define WRONG_H

#include <QDialog>

namespace Ui {
class Wrong;
}

class Wrong : public QDialog
{
    Q_OBJECT

public:
    explicit Wrong(QWidget *parent = nullptr);
    ~Wrong();

private:
    Ui::Wrong *ui;
};

#endif // WRONG_H
