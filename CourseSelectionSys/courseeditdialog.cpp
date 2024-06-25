#include "courseeditdialog.h"
#include "ui_courseeditdialog.h"
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlError>
#include<QDebug>
#include"listtable.h"


CourseEditDialog::CourseEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CourseEditDialog)
{
    ui->setupUi(this);
    setWindowTitle("编辑课程窗口");

    //创建mdb数据库中的数据交互口 query_2
    QSqlQuery query_2;

    //调用select_table  查询数据库里的内容 并显示在表格中
    select_table();
}

CourseEditDialog::~CourseEditDialog()
{
    delete ui;
}

//查询数据库里的内容 并显示在表格中
void CourseEditDialog::select_table()
{
    ui->listWidget->clear();
    QSqlQuery tquery;
    QString search_data =QString("select* from course");
    if(!tquery.exec(search_data))
    {
        qDebug()<<"Failed to do select_tabel in CourseEditDialog";
    }
    else
    {
        while (tquery.next())
        {
            //创建自定义条目ListTable 以将它添加到自己的窗口的listwidget中去
            ListTable* tTabel=new ListTable;
            QListWidgetItem* tSingleList=new QListWidgetItem;
            tSingleList->setSizeHint(QSize(1300,55));          //让ListWidgetItem的大小与ListTable的大小相同
            ui->listWidget->addItem(tSingleList);              //将大小相同的ListWidgetItem放入ListWidget中去
            ui->listWidget->setItemWidget(tSingleList,tTabel); //将这个Item用自定义ListTable视图覆盖

            //函数原型：void setTableInfo(QString tId,QString tName,QString tTimetable, int tcredit,int tsemester,QString tclassroom);
            //数据库参数顺序同上
            tTabel->setTableInfo(tquery.value("id").toString(),
                                 tquery.value("name").toString(),
                                 tquery.value("timetable").toString(),
                                 tquery.value("credit_num").toInt(),
                                 tquery.value("semester_num").toInt(),
                                 tquery.value("classroom").toString());
        }
    }

}

//点击“添加”按钮
//记录添加至数据库中 并进行表格刷新
void CourseEditDialog::on_btn_add_clicked()
{
    //提取lineEdit里的内容 并把它输入到数据库
    QString tId= ui->lineEdit_id->text();
    QString tName=ui->lineEdit_name->text();
    QString tTimetable=ui->lineEdit_time->text();
    QString tCredit=ui->lineEdit_credit->text();
    QString tSemester=ui->lineEdit_semester->text();
    QString tClassroom=ui->lineEdit_classroom->text();

    QSqlQuery tQuery;
    QString tstr=QString("insert into course (id,name,timetable,credit_num,semester_num,classroom)"
                         "values('%1','%2','%3',%4,%5,'%6');").arg(tId).arg(tName).arg(tTimetable).arg(tCredit.toInt())
                                                              .arg(tSemester.toInt()).arg(tClassroom);
    if(!tQuery.exec(tstr))
    {
        qDebug()<<"Failed to exec in on_btn_add_clicked()";
    }

    //调用更新函数
    renew();
}

//点击“删除”按钮
//在ListTable里即时删除 并进行表格刷新
void CourseEditDialog::on_btn_delete_clicked()
{
    //提取lineEdit_id里的内容 以它为primary key来识别数据
    QString tId= ui->lineEdit_id->text();

    QSqlQuery tQuery;
    QString tstr=QString("delete from course where id='%1';").arg(tId);
    if(!tQuery.exec(tstr))
    {
        qDebug()<<"Failed to exec in on_btn_delete_clicked()";
    }

    //调用更新函数
    renew();
}

//点击“修改”按钮
//对ListTable里的表格进行即时修改 并进行表格刷新
void CourseEditDialog::on_btn_modify_clicked()
{
    //提取lineEdit_id里的内容 以它为primary key来识别数据
    QString tId= ui->lineEdit_id->text();

    //先把数据删除 但不进行显示
    QSqlQuery tQuery;
    QString tstr=QString("delete from course where id='%1';").arg(tId);
    if(!tQuery.exec(tstr))
    {
        qDebug()<<"Failed to exec in on_btn_modify_clicked()";
    }

    //提取lineEdit里面的内容 准备将数据插入数据库
    QString tName=ui->lineEdit_name->text();
    QString tTimetable=ui->lineEdit_time->text();
    QString tCredit=ui->lineEdit_credit->text();
    QString tSemester=ui->lineEdit_semester->text();
    QString tClassroom=ui->lineEdit_classroom->text();

    QString tstr_1=QString("insert into course (id,name,timetable,credit_num,semester_num,classroom)"
                         "values('%1','%2','%3',%4,%5,'%6');").arg(tId).arg(tName).arg(tTimetable).arg(tCredit.toInt())
                                                              .arg(tSemester.toInt()).arg(tClassroom);
    if(!tQuery.exec(tstr_1))
    {
        qDebug()<<"Failed to exec in on_btn_modify_clicked()";
    }

    //调用更新函数
    renew();
}

//更新函数：将lineEdit里内容清空 并在listTable进行刷新
void CourseEditDialog::renew()
{
    //点击“修改”按钮后 lineEdit里的内容清空
    ui->lineEdit_id->clear();
    ui->lineEdit_name->clear();
    ui->lineEdit_time->clear();
    ui->lineEdit_credit->clear();
    ui->lineEdit_semester->clear();
    ui->lineEdit_classroom->clear();
    //重新查询数据库中内容 及时更新
    select_table();
}

