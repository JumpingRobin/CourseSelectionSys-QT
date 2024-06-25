#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QString>
#include"student.h"
#include"classinfo.h"
#include"studenttable.h"
#include<QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool CheckCourse(QString);                 //检测是否数据库里有当前选择课程的函数
    void AddIntoStudent(Student&,QString);     //将数据库里的课程对象数据呈递给学生向量中的课程数组
    void ShowStudentsTable();                  //展示当前学生的个人信息汇总

    void ShowStudentsCourse(Student&);         //重载上函数 方便点击“开始选课”后调用 不需要再次输入学号即可查询

    void ShowSpecificClass();                  //展示特定课程的表格

    void InsertDatatoUser();                   //将数据初始化到user数据表中

    void LoginIn();                            //登录函数 用以决定登录的用户是管理员端还是用户端
                                               //即确定mStatus的取值问题

    void ShowInfo();                           //展示当前登录学生的信息 需要遍历与取出

    void WriteJson();                          //将数据写到JSON文件中的函数


private slots:
    void on_actionadd_s_triggered();

    void on_actionstart_c_triggered();

    void on_actionback_triggered();

    void on_actionedit_c_triggered();

    void on_actionsave_triggered();

    void on_actionopen_triggered();

    void on_actionStudentCourse_triggered();

    void on_actionStudentsTable_triggered();

    void on_btn_check_clicked();

    void on_actionspecificClass_triggered();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_actionJSON_triggered();

private:
    Ui::MainWindow *ui;
    QSqlDatabase mdb;      //创建数据成员 QsqlDatabase类的对象mdb
    StudentTable table;    //table数据成员 里面含有一个QVector与一个int

    int mStatus;        //整形数据成员 记录现在的状态是学生模式还是管理员模式 初始化为0
                           //mCondition=0时表示学生模式 部分功能没有经过授权 不能使用
                           //mCondition=1时表示管理员模式 功能均可以使用
};
#endif // MAINWINDOW_H
