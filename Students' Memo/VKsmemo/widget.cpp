#include "widget.h"
#include "ui_widget.h"
#include <Qstring>
#include <iostream>
#include <QFile>
#include <QDataStream>
#include <QDate>
#include <vector>
#include "fix.h"
#include "fixre.h"
#include "fixcs.h"
#include "notice.h"
#include "user.h"
#include "game.h"
extern User user;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //个性化内容及窗口初始化
    InitApp();
    //课程部分初始化
    InitCourse();
    //作业部分初始化
    InitHomework();
    //提醒部分初始化
    InitRemind();
    //今天部分初始化
    InitToday();
}

Widget::~Widget()
{
    delete ui;
}
//-------------------------------------初始化化部分-----------------------------------
void Widget::InitApp()
{
    ui->MainStacked->setCurrentIndex(0);
    ui->coursenums->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]{2}")));
    QString color = user.GetUserColor();
    ChangeColor(color);
}

void Widget::InitCourse()
{
    ui->Xedit->setValidator(new QRegularExpressionValidator(QRegularExpression("[1-7]{1}")));
    ui->Y1edit->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]{2}")));
    ui->Y2edit->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]{2}")));
    int nums = user.GetUserCoursenums();
    coursemanage.CourseDelete(nums);
    ui->CourseTable->setRowCount(nums);//便于设置更改
    ui->CourseTable->setColumnCount(7);
    ui->CourseTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //自适应列宽
    ui->CourseTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch); //自适应行高
    ui->CourseTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->infoswitch->hide();
    ui->infoteacher->setReadOnly(1);
    ui->infoteacher->setFont(QFont("华文新魏",16));
    ui->inforoom->setReadOnly(1);
    ui->inforoom->setFont(QFont("华文新魏",16));
    ui->infoscore->setReadOnly(1);
    ui->infoscore->setFont(QFont("华文新魏",16));
    ui->infonote->setReadOnly(1);
    ui->infonote->setFont(QFont("华文新魏",16));
    ShowCourse();
}

void Widget::InitHomework()
{
    ui->HomeworkStacked->setCurrentIndex(0);
    ui->HomeworkTable_1->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->HomeworkTable_1->setColumnCount(6);
    ui->HomeworkTable_1->setColumnWidth(0,95);
    ui->HomeworkTable_1->setColumnWidth(1,220);
    ui->HomeworkTable_1->setColumnWidth(2,145);
    ui->HomeworkTable_1->setColumnWidth(3,60);
    ui->HomeworkTable_1->setColumnWidth(4,125);
    ui->HomeworkTable_1->setColumnWidth(5,75);
    ui->HomeworkTable_1->horizontalHeader()->show();
    ui->levelhide->hide();
    ui->statushide->hide();
    ShowHomework();

}

void Widget::InitRemind()
{
    ui->RemindStacked->setCurrentIndex(0);
    ui->RemindTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->RemindTable->setColumnWidth(0,150);
    ui->RemindTable->setColumnWidth(1,360);
    ui->RemindTable->setColumnWidth(2,150);
    ShowRemind();
}

void Widget::on_coursenumsqd_clicked()
{
    if(!ui->coursenums->text().isEmpty())
    {
        QString num = ui->coursenums->text().toUtf8();
        user.ChangeUserCoursenums(num);
        ui->CourseTable->setRowCount(user.GetUserCoursenums());
        ui->CourseTable->update();
    }
}

//-------------------------------------主界面切换-----------------------------------
void Widget::on_btn_EXP_clicked()
{
    ui->CourseTable->update();
    ui->MainStacked->setCurrentIndex(0);
}

void Widget::on_btn_course_clicked()
{

    ui->MainStacked->setCurrentIndex(1);
}

void Widget::on_btn_homework_clicked()
{
    ShowHomework();
    ui->HomeworkTable_1->update();
    ui->MainStacked->setCurrentIndex(2);
}

void Widget::on_btn_reminder_clicked()
{
    ShowRemind();
    ui->RemindTable->update();
    ui->MainStacked->setCurrentIndex(3);
}

void Widget::on_btn_setting_clicked()
{
    ui->MainStacked->setCurrentIndex(4);
}

void Widget::on_btn_quit_clicked()
{
    QApplication* app;
    app->exit(0);
}

//--------------------------------------------课程部分-------------------------------------------
void Widget::ClearCourse()
{
    ui->CourseTable->clear();
}

void Widget::AddCourse()
{
    int x;//横坐标，周数本身
    int y1;//开始节数
    int y2;//结束节数
    int score;//学分
    QString classname;//课程名
    QString teacher;//老师
    QString classroom;//教室
    QString note;//备注
    classname = ui->csnameedit->text();
    teacher = ui->teachedit->text();
    classroom = ui->roomedit->text();
    note = ui->noteedit->toPlainText();
    x = ui->Xedit->text().toInt();
    y1 = ui->Y1edit->text().toInt();
    y2 = ui->Y2edit->text().toInt();
    score = ui->scoreedit->text().toInt();
    Course* add = new Course(x,y1,y2,score,classname,teacher,classroom,note);
    Nodecs* Cnew = new Nodecs;
    Cnew->val = *add;
    Cnew->next = NULL;
    add->SaveCourse(Cnew);
    ShowCourse();
}

void Widget::ShowCourse()
{
    ClearCourse();
    Nodecs* Head = coursemanage.CourseFetch();
    Nodecs* Current = Head;
    while(Current)
    {
        int x = Current->val.GetX()-1;
        int y1 = Current->val.GetY1()-1;
        int y2 = Current->val.GetY2()-1;
        for(int i = y1; i <= y2; i++)
        {
            QString classname = Current->val.GetName();
            QTableWidgetItem* iclassname = new QTableWidgetItem(classname);
            ui->CourseTable->setItem(i,x,iclassname);
            ui->CourseTable->item(i,x)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            ui->CourseTable->item(i,x)->setFont(QFont("华文新魏",16));
            iclassname = NULL;
        }
        Current = Current->next;
    }

    ui->CourseTable->update();
}

void Widget::on_searchname_editingFinished()//输入内容后回车
{
    DisplayResult();
}

void Widget::on_search_clicked()//点击搜索按钮
{
    DisplayResult();
}

void Widget::on_btn_showCourseTable_clicked()
{
    ShowCourse();
    ui->CourseTable->update();
    ui->CourseStacked->setCurrentIndex(0);
}

void Widget::on_btn_change_clicked()
{
    ShowCourse();
    ui->CourseTable->update();
    ui->CourseStacked->setCurrentIndex(0);
    fixcs* change = new fixcs;
    change->show();
}

void Widget::on_savecourse_clicked()
{
    if(!(ui->csnameedit->text().isEmpty())&&(!(ui->Xedit->text().isEmpty()))
        &&(!(ui->Y1edit->text().isEmpty()))&&(!(ui->Y2edit->text().isEmpty()))
        &&(ui->Y1edit->text().toInt())<=(ui->Y2edit->text().toInt()))
    {
        AddCourse();
        ui->csnameedit->text().clear();
        ui->teachedit->text().clear();
        ui->scoreedit->text().clear();
        ui->roomedit->text().clear();
        ui->Xedit->text().clear();
        ui->Y1edit->text().clear();
        ui->Y2edit->text().clear();
        ui->noteedit->toPlainText().clear();
        ui->CourseStacked->setCurrentIndex(0);
    }
    else
    {
        Notice* notice = new Notice;
        notice->show();
    }

}

void Widget::on_btn_addcourse_clicked()
{
    ui->CourseStacked->setCurrentIndex(1);
}

void Widget::on_btn_info_clicked()
{
    ui->infoswitch->hide();
    ui->searchname->text().clear();
    ui->CourseStacked->setCurrentIndex(2);
}

void Widget::DisplayResult()
{
    ui->infoswitch->show();
    if(!ui->searchname->text().isEmpty())
    {
        QString name = ui->searchname->text();
        Nodecs* answer = coursemanage.CourseSearch(name);
        if(answer)
        {
            QString teacher;
            QString room;
            QString score;
            QString note;
            teacher = answer->val.GetTeach();
            room = answer->val.GetRoom();
            score = QString::number(answer->val.GetScore());
            note = answer->val.GetNote();
            ui->infoteacher->setText(teacher);
            ui->inforoom->setText(room);
            ui->infoscore->setText(score);
            ui->infonote->setText(note);
            ui->infoswitch->setCurrentIndex(1);
        }
        else
        {
            ui->infoswitch->setCurrentIndex(0);
        }
    }
}
//-----------------------------------------作业界面-----------------------------------------------
//展示作业列表
void Widget::on_btn_showHW_2_clicked()
{
    ShowHomework();
    ui->HomeworkTable_1->update();
    ui->HomeworkStacked->setCurrentIndex(0);
}

//添加模块
void Widget::AddHomework()
{
    QString name;
    QString content;
    //QString amount;
    QString level;
    QString finish;
    QString submission;
    int year;
    int month;
    int date;
    int hour;
    int min;
    name = ui->nameedit->text();
    content = ui->contentedit->toPlainText();
    submission = ui->submissionedit->text();
    qDebug()<<submission;
    year = ui->DDL->date().year();
    month = ui->DDL->date().month();
    date = ui->DDL->date().day();
    hour = ui->DDL->time().hour();
    min = ui->DDL->time().minute();
    if(ui->level->isChecked())//重要程度
    {
        level = "重要";
    }
    else if(ui->level_2->isChecked())
    {
        level = "一般";
    }
    else if(ui->level_3->isChecked())
    {
        level = "不重要";
    }
    if(ui->status->isChecked())//完成情况
    {
        finish = "未完成";
    }
    else if(ui->status_2->isChecked())
    {
        finish = "已完成";
    }
    //时间不会为空，但是课程名和作业内容必须有值，其他部分不填就算了
    Homework* hw_add = new Homework(name,content,level,finish,submission,year,month,date,hour,min);
    qDebug()<< hw_add->GetSubmission();
    Nodehw* pNew = new Nodehw;
    pNew->val = *hw_add;
    pNew->next = NULL;
    homeworkmanage.Save(pNew);
    ShowHomework();
}

void Widget::ShowHomework()
{
    ClearHomework();
    Nodehw* Head = homeworkmanage.Arrange(homeworkmanage.Fetch());
    Nodehw* Current = Head;
    while(Current)
    {
        qDebug()<<Current;
        QString name = Current->val.GetName();
        qDebug()<<name;
        QString content = Current->val.GetContent();
        QString level = Current->val.GetLevel();
        QString finish = Current->val.GetFinish();
        QString submission = Current->val.GetSubmission();
        int year = Current->val.GetYear();
        int month = Current->val.GetMonth();
        int date = Current->val.GetDate();
        int hour = Current->val.GetHour();
        int min = Current->val.GetMin();
        ui->HomeworkTable_1->setRowCount((ui->HomeworkTable_1->rowCount()+1));
        int row = (ui->HomeworkTable_1->rowCount())-1;
        QTableWidgetItem* iname = new QTableWidgetItem(name);
        QTableWidgetItem* icontent = new QTableWidgetItem(content);
        QTableWidgetItem* iDDL = new QTableWidgetItem(QString::number(year)+"-"+QString::number(month)+"-"+QString::number(date)
                                                      +"-"+QString::number(hour)+":"+QString::number(min));
        QTableWidgetItem* ilevel = new QTableWidgetItem(level);
        QTableWidgetItem* isubmission = new QTableWidgetItem(submission);
        QTableWidgetItem* ifinish= new QTableWidgetItem(finish);
        ui->HomeworkTable_1->setItem(row, 0, iname);
        ui->HomeworkTable_1->setItem(row, 1, icontent);
        ui->HomeworkTable_1->setItem(row, 2, iDDL);
        ui->HomeworkTable_1->setItem(row, 3, ilevel);
        ui->HomeworkTable_1->setItem(row, 4, isubmission);
        ui->HomeworkTable_1->setItem(row, 5, ifinish);
        for(int i = 0; i <= 5; i++)
        {
            if(i==3)
            {
                ui->HomeworkTable_1->item(row, i)->setFont(QFont("华文新魏",12));
                continue;
            }
            ui->HomeworkTable_1->item(row, i)->setFont(QFont("华文新魏",14));
        }
        Current = Current->next;
    }
    ui->HomeworkTable_1->update();
}

void Widget::ClearHomework()
{
    ui->HomeworkTable_1->clear();
    ui->HomeworkTable_1->setRowCount(0);
}

void Widget::on_savehomework_clicked()//添加保存
{
    //时间不会为空，但是课程名和作业内容必须有值，其他部分不填就算了
    if(!(ui->nameedit->text().isEmpty())&&(!(ui->contentedit->toPlainText().isEmpty())))
    {
        AddHomework();
        ui->nameedit->clear();
        ui->contentedit->clear();
        ui->DDL->clear();
        ui->submissionedit->clear();
        ui->levelhide->setChecked(true);
        ui->statushide->setChecked(true);
        ui->HomeworkStacked->setCurrentIndex(0);
    }
    else
    {
        Notice* notice = new Notice;
        notice->show();
    }

}

void Widget::on_btn_addHW_2_clicked()
{
    ui->HomeworkStacked->setCurrentIndex(1);
}

void Widget::on_btn_changeHW_2_clicked()
{
    ShowHomework();
    ui->HomeworkStacked->setCurrentIndex(0);
    Fix* change = new Fix;
    change->show();
}

void Widget::ChangeFinish(int num, int b)
{
    int count = 1;
    Nodehw* head = homeworkmanage.Arrange(homeworkmanage.Fetch());//时间升序
    Nodehw* current = head;
    QDate today_date(QDate::currentDate());
    int today_year = today_date.year();
    int today_month = today_date.month();
    int today_day = today_date.day();
    while(current)
    {
        if((current->val.GetYear() > today_year)
            ||(current->val.GetYear() == today_year&&current->val.GetMonth() > today_month)
            ||(current->val.GetYear() == today_year&&current->val.GetMonth() == today_month&&current->val.GetDate() > today_day))
        {
            break;
        }
        if(current->val.GetYear() == today_year
            &&current->val.GetMonth() == today_month
            &&current->val.GetDate() == today_day&&current->val.GetFinish() == "未完成")
        {
            if(count == num)
            {
                if(b == 1)
                {
                    current->val.SetFinish("已完成");
                }
                else if(b == 0)
                {
                    current->val.SetFinish("未完成");
                }
                break;
            }
            else
            {
                count++;
            }
        }
        current = current->next;
    }
    QFile file(user.GetFilenamehw());
    if(!file.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {
        qDebug()<<"failed to open hwfile";
    }
    QDataStream fin(&file);
    current = head;
    while(current)
    {
        fin<<current->val;
        current = current->next;
    }
    file.close();
}
//------------------------------------------------提醒部分-----------------------------------------------
//提醒界面切换
void Widget::on_btn_addAC_3_clicked()
{
    ui->RemindStacked->setCurrentIndex(1);
}

void Widget::on_btn_showAC_3_clicked()
{
    ShowRemind();
    ui->RemindTable->update();
    ui->RemindStacked->setCurrentIndex(0);
}

void Widget::on_btn_changeAC_3_clicked()
{
    ShowRemind();
    ui->RemindStacked->setCurrentIndex(0);
    FixRE* change_ac = new FixRE;
    change_ac->show();
}

void Widget::ClearRemind()
{
    ui->RemindTable->clear();
    ui->RemindTable->setRowCount(0);
}

void Widget::AddRemind()
{
    QString organizer = ui->organizer->text();
    QString accontent = ui->activity->toPlainText();
    int year = ui->appointtime->date().year();
    int month = ui->appointtime->date().month();
    int date = ui->appointtime->date().day();
    int hour = ui->appointtime->time().hour();
    int min = ui->appointtime->time().minute();
    Remind* add = new Remind(organizer, accontent, year, month, date, hour, min);
    Noderm* Rnew = new Noderm;
    Rnew->val = *add;
    Rnew->next = NULL;
    remindmanage.Save(Rnew);
    ShowRemind();
}

void Widget::ShowRemind()
{
    ClearRemind();
    Noderm* Head = remindmanage.Arrange(remindmanage.Fetch());
    Noderm* Current = Head;
    while(Current)
    {
        qDebug()<<Current;
        QString organizer;
        QString accontent;
        int year;
        int month;
        int date;
        int hour;
        int min;
        organizer = Current->val.GetOrganizer();
        accontent = Current->val.GetAcContent();
        year = Current->val.GetYear();
        month = Current->val.GetMonth();
        date = Current->val.GetDate();
        hour = Current->val.GetHour();
        min = Current->val.GetMin();
        int row = ui->RemindTable->rowCount();
        ui->RemindTable->setRowCount(row+1);
        QTableWidgetItem* iorganizer = new QTableWidgetItem(organizer);
        QTableWidgetItem* iaccontent = new QTableWidgetItem(accontent);
        QTableWidgetItem* iappointedtime = new QTableWidgetItem(QString::number(year)+"-"+QString::number(month)
                                                                +"-"+QString::number(date)+"-"+QString::number(hour)+":"+QString::number(min));
        ui->RemindTable->setItem(row, 0, iorganizer);
        ui->RemindTable->setItem(row, 1, iaccontent);
        ui->RemindTable->setItem(row, 2, iappointedtime);
        for(int i = 0; i <= 2; i++)
        {
            ui->RemindTable->item(row, i)->setFont(QFont("华文新魏",14));
        }
        Current = Current->next;
    }
    ui->RemindTable->update();
}


void Widget::on_saveremind_clicked()
{
    if(!(ui->activity->toPlainText().isEmpty()))//活动项目必填
    {
        AddRemind();
        ui->activity->clear();
        ui->organizer->clear();
        ui->appointtime->clear();
        ui->RemindStacked->setCurrentIndex(0);
    }
    else
    {
        Notice* notice = new Notice;
        notice->show();
    }
}

void Widget::ChangeColor(QString color)
{
    this->setStyleSheet("background-color:"+color);
    ui->Label_Setting->setStyleSheet("background-color:"+color);
    ui->label_AddAC->setStyleSheet("background-color:"+color);
    ui->label_AddRM->setStyleSheet("background-color:"+color);
    ui->label_Course->setStyleSheet("background-color:"+color);
    ui->label_Homework->setStyleSheet("background-color:"+color);
    ui->label_ACremind->setStyleSheet("background-color:"+color);
    ui->label_Today->setStyleSheet("background-color:"+color);
}

void Widget::on_ColorBox_textActivated(const QString &arg1)//Change Color
{
    QString color;
    if(arg1 == "B站粉")
    {
        color = "rgb(245, 190, 197)";
    }
    else if(arg1 == "WHU绿")
    {
        color = "rgb(17, 87, 64)";
    }
    else if(arg1 == "THU紫")
    {
        color = "rgb(89, 13, 99)";
    }
    user.ChangeUserColor(color);
    ChangeColor(color);
}

//------------------------------------------今天部分-----------------------------------------
void Widget::on_btn_trueremind_clicked()
{
    InitToday();
    ui->MainStacked->setCurrentIndex(5);
}

void Widget::InitToday()
{
    ui->cz->hide();
    ui->yjj->hide();
    QDate today_date(QDate::currentDate());
    int today_year = today_date.year();
    int today_month = today_date.month();
    int today_day = today_date.day();
    TodayHomework(today_year,today_month,today_day);
    TodayRemind(today_year,today_month,today_day);
}

void Widget::TodayHomework(int today_year, int today_month, int today_day)
{
    //------------------------初始化作业----------------------
    Homework manage;
    Nodehw* head = manage.Arrange(manage.Fetch());//时间升序
    Nodehw* current = head;
    vector<Nodehw*> todayhw;
    while(current)
    {
        if((current->val.GetYear() > today_year)
            ||(current->val.GetYear() == today_year&&current->val.GetMonth() > today_month)
            ||(current->val.GetYear() == today_year&&current->val.GetMonth() == today_month&&current->val.GetDate() > today_day))
        {
            break;
        }
        if(current->val.GetYear() == today_year&&current->val.GetMonth() == today_month
            &&current->val.GetDate() == today_day&&current->val.GetFinish() == "未完成")
        {
            todayhw.push_back(current);
        }
        current = current->next;
    }
    Homework Kong;
    Kong.SetContent(" ");
    Kong.SetName(" ");
    Nodehw kong;
    kong.val = Kong;
    kong.next = NULL;
    todayhw.resize(6,&kong);
    QCheckBox* chehw[6] = {ui->che_hk_1,ui->che_hk_2,ui->che_hk_3,ui->che_hk_4,ui->che_hk_5,ui->che_hk_6};
    QString chehw1 = todayhw[0]->val.GetName();
    chehw1 += "——";
    chehw1 += todayhw[0]->val.GetContent();
    QString chehw2 = todayhw[1]->val.GetName();
    chehw2 += "——";
    chehw2 += todayhw[1]->val.GetContent();
    QString chehw3 = todayhw[2]->val.GetName();
    chehw3 += "——";
    chehw3 += todayhw[2]->val.GetContent();
    QString chehw4 = todayhw[3]->val.GetName();
    chehw4 += "——";
    chehw4 += todayhw[3]->val.GetContent();
    QString chehw5 = todayhw[4]->val.GetName();
    chehw5 += "——";
    chehw5 += todayhw[4]->val.GetContent();
    QString chehw6 = todayhw[5]->val.GetName();
    chehw6 += "——";
    chehw6 += todayhw[5]->val.GetContent();
    QString hwcon[6] = {chehw1,chehw2,chehw3,chehw4,chehw5,chehw6};
    int cz = 0;
    for(int i = 0; i < 6; i++)
    {
        chehw[i]->setText(hwcon[i]);
        if(hwcon[i] == " —— ")
        {
            chehw[i]->hide();
        }
        else
        {
            chehw[i]->show();
            cz++;
        }
    }
    if(cz == 0)
    {
        ui->cz->show();
    }
}

void Widget::TodayRemind(int today_year, int today_month, int today_day)
{
    Remind manage;
    Noderm* head = manage.Arrange(manage.Fetch());//时间升序
    Noderm* current = head;
    vector<Noderm*> todayrm;
    while(current)
    {

        if((current->val.GetYear() > today_year)
            ||(current->val.GetYear() == today_year&&current->val.GetMonth() > today_month)
            ||(current->val.GetYear() == today_year&&current->val.GetMonth() == today_month&&current->val.GetDate() > today_day))
        {
            break;
        }
        if(current->val.GetYear() == today_year
            &&current->val.GetMonth() == today_month
            &&current->val.GetDate() == today_day)
        {
            todayrm.push_back(current);
        }
        current = current->next;
    }

    Remind Kong;
    Kong.SetAcConnent(" ");
    Kong.SetOrganizer(" ");
    Noderm kong;
    kong.val = Kong;
    kong.next = NULL;
    todayrm.resize(6,&kong);
    QLabel* cherm[6] = {ui->che_ac_1,ui->che_ac_2,ui->che_ac_3,ui->che_ac_4,ui->che_ac_5,ui->che_ac_6};
    QString cherm1 = todayrm[0]->val.GetOrganizer();
    cherm1 += "——";
    cherm1 += todayrm[0]->val.GetAcContent();
    QString cherm2 = todayrm[1]->val.GetOrganizer();
    cherm2 += "——";
    cherm2 += todayrm[1]->val.GetAcContent();
    QString cherm3 = todayrm[2]->val.GetOrganizer();
    cherm3 += "——";
    cherm3 += todayrm[2]->val.GetAcContent();
    QString cherm4 = todayrm[3]->val.GetOrganizer();
    cherm4 += "——";
    cherm4 += todayrm[3]->val.GetAcContent();
    QString cherm5 = todayrm[4]->val.GetOrganizer();
    cherm5 += "——";
    cherm5 += todayrm[4]->val.GetAcContent();
    QString cherm6 = todayrm[5]->val.GetOrganizer();
    cherm6 += "——";
    cherm6 += todayrm[5]->val.GetAcContent();
    QString rmcon[6] = {cherm1,cherm2,cherm3,cherm4,cherm5,cherm6};
    int yjj = 0;
    for(int i = 0; i < 6; i++)
    {
        cherm[i]->setText(rmcon[i]);
        if(rmcon[i] == " —— ")
        {
            cherm[i]->hide();
        }
        else
        {
            cherm[i]->show();
            yjj++;
        }
    }
    if(yjj == 0)
    {
        ui->yjj->show();
    }
}

void Widget::on_che_hk_1_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        ChangeFinish(1,1);
    }
    else if(arg1 == 0)
    {
        ChangeFinish(1,0);
    }
}

void Widget::on_che_hk_2_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        ChangeFinish(2,1);
    }
    else if(arg1 == 0)
    {
        ChangeFinish(2,0);
    }
}

void Widget::on_che_hk_3_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        ChangeFinish(3,1);
    }
    else if(arg1 == 0)
    {
        ChangeFinish(3,0);
    }
}

void Widget::on_che_hk_4_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        ChangeFinish(4,1);
    }
    else if(arg1 == 0)
    {
        ChangeFinish(4,0);
    }
}

void Widget::on_che_hk_5_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        ChangeFinish(5,1);
    }
    else if(arg1 == 0)
    {
        ChangeFinish(5,0);
    }
}

void Widget::on_che_hk_6_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        ChangeFinish(6,1);
    }
    else if(arg1 == 0)
    {
        ChangeFinish(6,0);
    }
}

void Widget::on_pushButton_clicked()
{
    if(eggflag)
    {
        game* g = new game;
        g->show();
        eggflag = 0;
    }
}

