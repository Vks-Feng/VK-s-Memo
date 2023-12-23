#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "Course.h"
#include "Homework.h"
#include "Remind.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    Course coursemanage;
    Homework homeworkmanage;
    Remind remindmanage;
    bool eggflag = 1;
private slots:
    void InitApp();
    //-------------------------------主界面切换部分-----------------------------------
    void on_btn_EXP_clicked();//切换到welcome&关于界面

    void on_btn_trueremind_clicked();//切换到今天界面

    void on_btn_course_clicked();//切换到课程界面

    void on_btn_homework_clicked();//切换到作业界面

    void on_btn_reminder_clicked();//切换到提醒界面

    void on_btn_setting_clicked();//切换到设置界面

    void on_btn_quit_clicked();//退出程序
    //---------------------------------------课程----------------------------------
    void InitCourse();

    void AddCourse();//添加课程

    void ShowCourse();//展示课表

    void on_btn_change_clicked();//弹出修改课程小窗

    void ClearCourse();//清空（防止显示错误）

    void on_btn_info_clicked();//切换到搜索信息界面

    void on_searchname_editingFinished();//输入搜索内容后敲击回车

    void on_search_clicked();//点击搜索按钮

    void DisplayResult();//搜索结果

    void on_savecourse_clicked();//保存按下

    void on_btn_addcourse_clicked();//添加界面

    void on_btn_showCourseTable_clicked();//展示界面

   //--------------------------------------作业界面------------------------------------------
    void InitHomework();

    void on_btn_showHW_2_clicked();//作业界面下展示界面

    void on_btn_addHW_2_clicked();//作业界面下添加作业

    void on_savehomework_clicked();//作业添加保存按钮

    void AddHomework();//添加作业

    void ShowHomework();//展示作业

    void ClearHomework();//清空展示表（防止错误显示）

    void on_btn_changeHW_2_clicked();//作业界面下修改（小窗）

    void ChangeFinish(int num, int b);//今天界面下改变作业完成状态

    //--------------------------------------提醒界面-------------------------------------------
    void InitRemind();

    void on_btn_addAC_3_clicked();//提醒界面下添加活动界面

    void on_btn_showAC_3_clicked();//提醒界面下展示界面

    void on_btn_changeAC_3_clicked();//提醒界面下修改界面

    void on_saveremind_clicked();//保存按下

    void AddRemind();

    void ShowRemind();

    void ClearRemind();

    //---------------------------------今天部分-----------------------------

    void InitToday();

    void TodayHomework(int today_year, int today_month, int today_day);

    void TodayRemind(int today_year, int today_month, int today_day);

    void on_che_hk_1_stateChanged(int arg1);

    void on_che_hk_2_stateChanged(int arg1);

    void on_che_hk_3_stateChanged(int arg1);

    void on_che_hk_4_stateChanged(int arg1);

    void on_che_hk_5_stateChanged(int arg1);

    void on_che_hk_6_stateChanged(int arg1);

    //---------------------------------设置---------------------------------
    void on_coursenumsqd_clicked();

    void on_ColorBox_textActivated(const QString &arg1);

    void ChangeColor(QString color);

    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
