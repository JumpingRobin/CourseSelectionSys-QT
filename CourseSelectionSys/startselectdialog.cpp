#include "startselectdialog.h"
#include "ui_startselectdialog.h"
#include"listtable.h"
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlError>
#include<QDebug>
#include<QMessageBox>


StartSelectDialog::StartSelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartSelectDialog)
{
    ui->setupUi(this);

    setWindowTitle("学生选课窗口");
    select_table();                   //查询可选课程表
}

StartSelectDialog::~StartSelectDialog()
{
    delete ui;
}

//查询数据库里的内容 并显示在表格中
void StartSelectDialog::select_table()
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
            ui->listWidget->addItem(tSingleList);             //将大小相同的ListWidgetItem放入ListWidget中去
            ui->listWidget->setItemWidget(tSingleList,tTabel);//将这个Item用自定义ListTable视图覆盖

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

//返回被选中的课的ID
QString StartSelectDialog::getSelectId()
{
    return ui->lineEdit_id->text();
}

//返回被选中学生的ID
QString StartSelectDialog::getSelectIdOfStudent()
{
    return ui->lineEdit_id_03->text();
}


//点击“选课”按钮
void StartSelectDialog::on_btn_add_clicked()
{
    if(ui->lineEdit_id->text().isEmpty())
    {
        //弹出一个提示对话框 提醒用户不能为空
        QMessageBox::information(this,"选课提示","课程编号不能为空");
    }
    else
    {
        //向主窗口发出accept()信号  返回主线程
        accept();
    }
}

//点击“退选”按钮
void StartSelectDialog::on_btn_delete_clicked()
{
    if(ui->lineEdit_id->text().isEmpty())
    {
        //弹出一个提示对话框 提醒用户不能为空
        QMessageBox::information(this,"退选提示","课程编号不能为空");
    }
    else
    {
        //向主窗口发出reject()信号  返回主线程
        reject();
    }

}

