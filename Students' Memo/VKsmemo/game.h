#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QLabel>
#include <QTime>
#include <ctime>
#include <QKeyEvent>
#include <QEvent>

namespace Ui {
class game;
}

class game : public QWidget
{
    Q_OBJECT

public:
    explicit game(QWidget *parent = nullptr);

    void LinkLabel();//将label的指针存进二维数组

    void InitMathBoard();//初始化算术数组

    void LabelHide();//正常显示

    void LabelShow();//正常显示

    void InttoLabel();//把int算术板中的数组传到label中

    void LabelStyle();//设置字体

    void RandomNum();//随机生成数字

    void keyPressEvent(QKeyEvent *event);

    void Upprocess();//向上

    void Downprocess();//向下

    void Leftprocess();//向左

    void Rightprocess();//向右

    void GameStart();//开始游戏

    bool BoardFull();//判断棋盘是否已满

    //void PlayerMove();//读取按键并判断

    bool IsLoserow();//判断横排

    bool IsLosecol();//判断纵列

    void Over();

    ~game();

private slots:

    void on_btn_left_clicked();//左移

    void on_btn_right_clicked();//右移

    void on_btn_down_clicked();//下移

    void on_btn_up_clicked();//上移

private:
    Ui::game *ui;
    QLabel* arr[4][4];
    int MathBoard[4][4];
};


#endif // GAME_H
