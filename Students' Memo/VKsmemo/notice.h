#ifndef NOTICE_H
#define NOTICE_H

#include <QWidget>

namespace Ui {
class Notice;
}

class Notice : public QWidget
{
    Q_OBJECT

public:
    explicit Notice(QWidget *parent = nullptr);
    ~Notice();

private slots:
    void on_noticecon_clicked();

private:
    Ui::Notice *ui;
};

#endif // NOTICE_H
