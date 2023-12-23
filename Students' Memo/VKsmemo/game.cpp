#include "game.h"
#include "ui_game.h"


game::game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::game)
{
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());
    setFocusPolicy(Qt::StrongFocus);
    ui->OverNotice->hide();
    LinkLabel();
    LabelStyle();
    InitMathBoard();
    InttoLabel();
}

game::~game()
{
    delete ui;
}

void game::LinkLabel()
{
    arr[0][0] = ui->l00;
    arr[1][0] = ui->l10;
    arr[2][0] = ui->l20;
    arr[3][0] = ui->l30;
    arr[0][1] = ui->l01;
    arr[1][1] = ui->l11;
    arr[2][1] = ui->l21;
    arr[3][1] = ui->l31;
    arr[0][2] = ui->l02;
    arr[1][2] = ui->l12;
    arr[2][2] = ui->l22;
    arr[3][2] = ui->l32;
    arr[0][3] = ui->l03;
    arr[1][3] = ui->l13;
    arr[2][3] = ui->l23;
    arr[3][3] = ui->l33;
}

void game::LabelStyle()
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            arr[i][j]->setAlignment(Qt::AlignCenter);
            arr[i][j]->setFont(QFont("方正粗黑宋简体",20));
        }
    }
}


void game::InitMathBoard()
{
    //第一步：置空数组
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            MathBoard[i][j] = 0;
        }
    }
    //第二步：给初值
    std::srand(time(NULL));
    int n1 = rand() % 4 == 1 ? 4 : 2;
    int n2 = 2;
    int count = 0;
    while(1)
    {
        int x = rand()%4;
        int y = rand()%4;
        if(MathBoard[x][y] == 0)
        {
            if(count == 0)
            {
                MathBoard[x][y] = n1;
                count++;
            }
            else
            {
                MathBoard[x][y] = n2;
                break;
            }
        }
    }
}

void game::InttoLabel()
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(MathBoard[i][j] == 0)
            {
                arr[i][j]->setText(" ");
            }
            else
            {
                arr[i][j]->setText(QString::number(MathBoard[i][j]));
            }
        }
    }
}

void game::RandomNum()
{
    std::srand(time(NULL));
    while(1)
    {
        int x = rand()%4;
        int y = rand()%4;
        if(MathBoard[x][y] == 0)
        {
            MathBoard[x][y] = rand()%4 == 1 ? 4 : 2;
            break;
        }
    }
}

void game::LabelHide()
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            arr[i][j]->hide();
        }
    }
}

void game::LabelShow()
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            arr[i][j]->show();
        }
    }
}

void game::Upprocess()
{
    LabelHide();
    bool change = false;
    for (int i = 0; i < 4; i++)
    {
        int temp = 0;
        for (int j = temp + 1; j < 4; j++)
        {
            if (MathBoard[j][i] != 0)
            {
                if (MathBoard[j][i] == MathBoard[temp][i])
                {
                    MathBoard[temp][i] *= 2;
                    MathBoard[j][i] = 0;
                    temp++;
                    change = true;
                }
                else if (MathBoard[temp][i] == 0)
                {
                    MathBoard[temp][i] += MathBoard[j][i];
                    MathBoard[j][i] = 0;
                    change = true;
                }
                else if(MathBoard[temp][i] != MathBoard[j][i])
                {
                    if (j != temp + 1)
                    {
                        MathBoard[temp + 1][i] = MathBoard[j][i];
                        MathBoard[j][i] = 0;
                        temp++;
                        change = true;
                    }
                    else
                    {
                        temp++;
                    }
                }
            }
        }
    }
    if (change)
    {
        RandomNum();
    }
    InttoLabel();
    LabelShow();
    if(BoardFull())
    {
        Over();
    }
}

void game::Downprocess()
{
    LabelHide();
    bool change = false;
    for (int i = 0; i < 4; i++)
    {
        int temp = 3;
        for (int j = temp - 1; j >= 0; j--)
        {
            if (MathBoard[j][i] != 0)
            {
                if (MathBoard[j][i] == MathBoard[temp][i])
                {
                    MathBoard[temp][i] *= 2;
                    MathBoard[j][i] = 0;
                    temp--;
                    change = true;
                }
                else if (MathBoard[temp][i] == 0)
                {
                    MathBoard[temp][i] += MathBoard[j][i];
                    MathBoard[j][i] = 0;
                    change = true;
                }
                else if (MathBoard[temp][i] != MathBoard[j][i])
                {
                    if (j != temp - 1)
                    {
                        MathBoard[temp - 1][i] = MathBoard[j][i];
                        MathBoard[j][i] = 0;
                        temp--;
                        change = true;
                    }
                    else
                    {
                        temp--;
                    }
                }
            }
        }
    }
    if (change)
    {
        RandomNum();
    }
    InttoLabel();
    LabelShow();
    if(BoardFull())
    {
        Over();
    }
}

void game::Leftprocess()
{
    LabelHide();
    bool change = false;
    for (int i = 0; i < 4; i++)
    {
        int temp = 0;
        for (int j = temp + 1; j < 4; j++)
        {
            if (MathBoard[i][j] != 0)
            {
                if (MathBoard[i][j] == MathBoard[i][temp])
                {
                    MathBoard[i][temp] *= 2;
                    MathBoard[i][j] = 0;
                    temp++;
                    change = true;
                }
                else if (MathBoard[i][temp] == 0)
                {
                    MathBoard[i][temp] += MathBoard[i][j];
                    MathBoard[i][j] = 0;
                    change = true;
                }
                else if (MathBoard[i][temp] != MathBoard[i][j])
                {
                    if (j != temp + 1)
                    {
                        MathBoard[i][temp + 1] = MathBoard[i][j];
                        MathBoard[i][j] = 0;
                        temp++;
                        change = true;
                    }
                    else
                    {
                        temp++;
                    }
                }
            }
        }
    }
    if (change)
    {
        RandomNum();
    }
    InttoLabel();
    LabelShow();
    if(BoardFull())
    {
        Over();
    }
}

void game::Rightprocess()
{
    LabelHide();
    bool change = false;
    for (int i = 0; i < 4; i++)
    {
        int temp = 3;
        for (int j = temp - 1; j >=0; j--)
        {
            if (MathBoard[i][j] != 0)
            {
                if (MathBoard[i][j] == MathBoard[i][temp])
                {
                    MathBoard[i][temp] *= 2;
                    MathBoard[i][j] = 0;
                    temp--;
                    change = true;

                }
                else if (MathBoard[i][temp] == 0)
                {
                    MathBoard[i][temp] += MathBoard[i][j];
                    MathBoard[i][j] = 0;
                    change = true;
                }
                else if (MathBoard[i][temp] != MathBoard[i][j])
                {
                    if (j != temp - 1)
                    {
                        MathBoard[i][temp - 1] = MathBoard[i][j];
                        MathBoard[i][j] = 0;
                        temp--;
                        change = true;
                    }
                    else
                    {
                        temp--;
                    }
                }
            }
        }
    }
    if (change)
    {
        RandomNum();
    }
    InttoLabel();
    LabelShow();
    if(BoardFull())
    {
        Over();
    }
}

void game::on_btn_left_clicked()
{
    Leftprocess();
}


void game::on_btn_right_clicked()
{
    Rightprocess();
}

void game::on_btn_up_clicked()
{
    Upprocess();
}

void game::on_btn_down_clicked()
{
    Downprocess();
}

bool game::BoardFull()
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(MathBoard[i][j] == 0)
            {
                return false;
            }
        }
    }
    return true;
}

bool game::IsLoserow()
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(MathBoard[i][j]==MathBoard[i][j+1])
            {
                return false;
            }
        }
    }
    return true;
}

bool game::IsLosecol()
{
    for(int j = 0; j < 4; j++)
    {
        for(int i = 0; i < 3; i++)
        {
            if(MathBoard[i][j]==MathBoard[i+1][j])
            {
                return false;
            }
        }
    }
    return true;
}

void game::Over()
{
    if(IsLosecol()&&IsLoserow())
    {
        ui->OverNotice->show();
    }
}

void game::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_A || event->key() == Qt::Key_Left)
    {
        Leftprocess();
    }
    else if(event->key() == Qt::Key_D || event->key() == Qt::Key_Right)
    {
        Rightprocess();
    }
    else if(event->key() == Qt::Key_W || event->key() == Qt::Key_Up)
    {
        Upprocess();
    }
    else if(event->key() == Qt::Key_S || event->key() == Qt::Key_Down)
    {
        Downprocess();
    }
}
