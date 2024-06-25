#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMenuBar>
#include<QMenu>
#include"studentinfodialog.h"
#include"courseeditdialog.h"
#include<QStringList>
#include"startselectdialog.h"
#include<QDir>
#include<QFileDialog>
#include<QMessageBox>
#include<QTableWidget>
#include<QStringList>
#include<QJsonArray>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonValue>
#include<QFile>
#include<QByteArray>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Info.db 数据库名称
    mdb=QSqlDatabase::addDatabase("QSQLITE");          //与QSQLITE数据库建立连接
    mdb.setDatabaseName("Info.db");                    //数据库的名字 Info.db
    if(!mdb.open())                                    //尝试打开数据库并检测是否打开成功
    {
        qDebug()<<"Failed to open mdb Database"<<mdb.lastError();
    }

    //建立QSqlQuery对象与数据库交互
    QSqlQuery query_1;


    //数据表course (只需要添加一次
#if 0
    QString tcreate_table_1= QString("create table course ("
                                   "id qstring,"
                                   "name qstring,"
                                   "timetable qstring,"
                                   "credit_num int,"
                                   "semester_num int,"
                                   "classroom qstring);");   //在mdb中创建一个course数据表 里面包含课程的所有信息

    if(!query_1.exec(tcreate_table_1))
    {
        qDebug()<<"create table failed"<<mdb.lastError();
    }
#endif

    //向数据库course表内载入数据(只需要添加一次
#if 0
    QString tinsert_table1=QString("insert into course (id,name,timetable,credit_num,semester_num,classroom)"
                            "values('JS0001','数字电路逻辑','周四上午3-4',3,1,'教六302');");
    QString tinsert_table2=QString("insert into course (id,name,timetable,credit_num,semester_num,classroom)"
                            "values('JS0002','大学物理','周二上午1-2',3,2,'教八201');");
    QString tinsert_table3=QString("insert into course (id,name,timetable,credit_num,semester_num,classroom)"
                            "values('JS0003','程序设计','周三上午1-4',2,2,'教一103');");
    QString tinsert_table4=QString("insert into course (id,name,timetable,credit_num,semester_num,classroom)"
                            "values('JS0004','数学分析','周一上午1-3',6,2,'教六303');");
    QString tinsert_table5=QString("insert into course (id,name,timetable,credit_num,semester_num,classroom)"
                            "values('JS0005','英语笔译','周四下午6-7',2,1,'教七401');");
    QString tinsert_table6=QString("insert into course (id,name,timetable,credit_num,semester_num,classroom)"
                            "values('JS0006','体育太极拳','周四下午11-12',1,1,'桃园田径场');");

    query_1.exec(tinsert_table1);
    query_1.exec(tinsert_table2);
    query_1.exec(tinsert_table3);
    query_1.exec(tinsert_table4);
    query_1.exec(tinsert_table5);
    query_1.exec(tinsert_table6);
#endif


    //数据表user 只需要创建一次
    //在mdb里创建一个储存用户名与密码的数据库表
#if 0
    QString create_table_2=QString("create table users("
                                   "username qstring,"
                                   "password qstring);");
    if(!query_1.exec(create_table_2))
    {
        qDebug()<<"Failed to open mdb Database"<<query_1.lastError();
    }
#endif

    //向数据库users表内载入数据(只需要添加一次
#if 0
    InsertDatatoUser();
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////mStatus的状态：0--学生端   1--管理员端  2--未登录端//////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
    //初始化为未登录状态 在LoginIn函数中进行修改为未登录状态
    mStatus=2;

    //为主窗口重置文字 添加图标
    setWindowTitle("学生选课管理系统");
    setWindowIcon(QIcon(":/seuIcon.png"));
    ui->stackedWidget->setCurrentIndex(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}


//点击“管理学生”
void MainWindow::on_actionadd_s_triggered()
{
    if(mStatus==1)
   {
        StudentInfoDialog tdlg_01(this);  //t_dlg_01 指的是temporary dialog 临时对话框对象
        int tiret=tdlg_01.exec();           //出现模态界面

        //OK键被按下
        if(tiret==QDialog::Accepted)
        {
            Student tStudent;
            tStudent.setId(tdlg_01.getId());
            tStudent.setName(tdlg_01.getName());
            tStudent.setClass(tdlg_01.getClass());
            tStudent.setPhone(tdlg_01.getPhone());
            tStudent.setAddress(tdlg_01.getAddress());
            tStudent.setBirthday(tdlg_01.getBirthday());
            table.AddStudent(tStudent);                   //利用addStudent函数 将从其中lineEdit里提取的信息放入向量中
            ShowStudentsTable();                            //利用ShowStudentsTable()函数 将学生数据展示在表格中
        }

        if(tiret==QDialog::Rejected)
        {
            QString tStr=tdlg_01.getId();
            for(int i=0;i<table.getTotalNum();i++)
            {
                if(tStr==table.student_table[i].getId())
                {
                    table.DeleteStudent(i);
                }
            }
            ShowStudentsTable();                            //利用ShowStudentsTable()函数 将学生数据展示在表格中
        }
    }
    else
    {
        QMessageBox::information(this,"权限受限","没有权限执行这个操作");
    }
}
////////////////////////////添加、删除学生以及存储到文件的功能测试成功////////////////////////////////

//点击“开始选课”
void MainWindow::on_actionstart_c_triggered()
{
    StartSelectDialog tdlg_02(this);
    if(table.getTotalNum()==0&&mStatus==1)
    {
        QMessageBox::critical(this,"管理员提示","请先添加学生");
    }
    //存在学生对象 而且是登录状态
    else if(table.getTotalNum()!=0&&mStatus!=2)
    {
        //学生数量不为0 开始阻塞代码
        int ret=tdlg_02.exec();
        //若点击选课 则将数据库里的课程内容赋给学生向量中
        if(ret==QDialog::Accepted)
        {
            //检查数据库中是否有这样一个课程ID
            if(CheckCourse(tdlg_02.getSelectId()))
            //表示此时通过检测 数据库中存在这样一个课程对象
            {
                QString tStr=tdlg_02.getSelectId();               //用tStr接收StartSelectDialog 填写的选课名
                QString tStr_01=tdlg_02.getSelectIdOfStudent();   //用tStr_01接受填写的学生名

                int tcounter=0;
                for(int i=0;i<table.getTotalNum();i++)
                {
                    if(tStr_01==table.student_table[i].getId())
                    {
                        tcounter=i;
                    }
                }
                AddIntoStudent(table.student_table[tcounter],tStr);
                table.student_table[tcounter].miNum++;
                ShowStudentsCourse(table.student_table[tcounter]);
            }
            else
            {
                QMessageBox::critical(this,"选课提示","不存在该课程");
            }
        }

        //若用户点击退选
        if(ret==QDialog::Rejected)
        {

            if(CheckCourse(tdlg_02.getSelectId()))
            {
                QString tStr=tdlg_02.getSelectId();               //用tStr接收StartSelectDialog 填写的选课名
                QString tStr_01=tdlg_02.getSelectIdOfStudent();   //用tStr_01接受填写的学生名
                int tcounter_1=0;                                   //记录学生的编号

                for(int i=0;i<table.getTotalNum();i++)
                {
                    for(int j=0;j<table.student_table[i].miNum;j++)
                    {
                        if(table.student_table[i].getId()==tStr_01&&table.student_table[i].mCourse[j].msId==tStr&&j!=4)
                        {
                            tcounter_1=i; //记录学生编号为i
                            for(int k=j;k<table.student_table[i].miNum;k++)
                            {
                                table.student_table[i].mCourse[k]=table.student_table[i].mCourse[k+1];//j之后的编号左移
                            }
                            table.student_table[i].miNum--;
                        }
                    }
                }

                //重新对表格进行打印
               ShowStudentsCourse(table.student_table[tcounter_1]);
            }
        }
    }

    else if(table.getTotalNum()==0||mStatus==2)                    //对管理员 如果还没有学生或未登录状态都会触发以下代码
    {
        QMessageBox::information(this,"操作提示","请先登录再进行操作");
    }
}
///////////////////////////////////“开始选课”测试成功//////////////////////////////////////

//点击“管理选课”
void MainWindow::on_actionedit_c_triggered()
{
    if(mStatus==1)
    {
        CourseEditDialog tdlg_03(this);  //切换界面
        tdlg_03.exec();
    }
    else
    {
        QMessageBox::information(this,"权限受限","没有权限执行这个操作");
    }
}

//点击“退出”
void MainWindow::on_actionback_triggered()
{
    //如果是封面页 则退出程序 否则返回到登录窗口
    if(ui->stackedWidget->currentIndex()==1)
    {
        this->close();
    }
    else
    {
        ui->stackedWidget->setCurrentIndex(1);
        ui->lineEdit_username->clear();
        ui->lineEdit_password->clear();
    }
}


//用win系统默认的感觉将student_table向量中的数据保存到文件里
void MainWindow::on_actionsave_triggered()
{
    QString tCurPath = QDir::currentPath();              //获取对话框的路径
    QString tDlgTitle = "另存为一个文件";                  //弹出对话框的标题
    QString tFilter = "文本文件(*.txt);;所有文件(*.*)";    //文件类型选项
    QString tFileName=QFileDialog::getSaveFileName(this, tDlgTitle, tCurPath, tFilter);
    if(tFileName.isEmpty())                            //若填写的文件名为空，则返回
        return;

    table.SaveTabletoFile(tFileName);
}


//将文件夹里的文件打开 并存储到mainwindow下数据成员table里的向量中去
void MainWindow::on_actionopen_triggered()
{
    QString tCurPath = QDir::currentPath();
    QString tDlgTitle = "选择一个文件";
    QString tFilter = "文本文件(*.txt);;所有文件(*.*)";
    QString tFileName = QFileDialog::getOpenFileName(this, tDlgTitle, tCurPath, tFilter);
    if(tFileName.isEmpty())
        return;
    //创建成功，打开文件
    table.ReadFile(tFileName);

    if(mStatus==1)
    {
        ui->stackedWidget->setCurrentIndex(0);
        ShowStudentsTable();
    }
}

///////////////////////////////////////////////////////////////////////////////////
//////////////////////////界面index=0 是 学生数据汇总界面//////////////////////////////
//////////////////////////界面index=3 是 学生选课信息界面//////////////////////////////
//////////////////////////界面index=2 是 特定课程信息界面//////////////////////////////
//////////////////////////界面index=1 是 学生登录界面   //////////////////////////////
//////////////////////////界面index=4 是 学生端的信息展示界面//////////////////////////
///////////////////////////////////////////////////////////////////////////////////


//点击“查询”->“学生选课信息”
//界面切换
void MainWindow::on_actionStudentCourse_triggered()
{
    if(mStatus==1)
    {
        ui->stackedWidget->setCurrentIndex(3);
    }
    else if(mStatus==2)
    {
        QMessageBox::information(this,"操作提示","请先登录再进行操作");
    }
    else if(mStatus==0)             //当以学生账号登录时 可以直接查询自己的课表 而不用搜索
                                    //避免数据泄露 方便用户操作
    {
        ui->stackedWidget->setCurrentIndex(3);
        int ticounter=0;
        QString tId=ui->label_idx->text();

        //遍历学生table向量
        //找到登录后对应的学生编号
        //利用重载的ShowStudentsCourse 进行自动查询
        for(int i=0;i<table.getTotalNum();i++)
        {
            if(tId==table.student_table[i].getId())
            {
                ticounter=i;
                break;
            }
        }
        ShowStudentsCourse(table.student_table[ticounter]);
    }

}

//点击“查询”->“学生数据汇总”
//只有管理员有权限
void MainWindow::on_actionStudentsTable_triggered()
{
    if(mStatus==1)
    {
        ui->stackedWidget->setCurrentIndex(0);
        ShowStudentsTable();
    }
    else
    {
        QMessageBox::information(this,"权限受限","没有权限执行这个操作");
    }
}

//点击“查询” 在表格中展示个人选课信息
//由于有重载的ShowStudentCourse版本 这个按钮只会在管理员版本按下
void MainWindow::on_btn_check_clicked()
{
    QString tStr=ui->lineEdit_id01->text();
    int tcounter=0;
    for(int i=0;i<table.getTotalNum();i++)
    {
        if(table.student_table[i].getId()==tStr)
        {
            tcounter=i;
        }
    }

    ShowStudentsCourse(table.student_table[tcounter]);
}

//点击“查询”->“特定课程展示”
//只有管理员有权限
void MainWindow::on_actionspecificClass_triggered()
{
    if(mStatus==1)
    {
        ui->stackedWidget->setCurrentIndex(2);
    }
    else
    {
        QMessageBox::information(this,"权限受限","没有权限执行这个操作");
    }
}

//按下“特定课程查询”中的查询按钮
//由于“特定课程查询”只有管理员有权限 这个按钮也只有管理员有权限
void MainWindow::on_pushButton_clicked()
{
    ShowSpecificClass();
}

//登录并展示学生主页
void MainWindow::on_pushButton_2_clicked()
{
    LoginIn();
}

//点击“开始”->“保存为JSON”
void MainWindow::on_actionJSON_triggered()
{
    WriteJson();
}

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////以下为辅助函数////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

//检测是否数据库里有当前选择课程的函数
//返回值为bool 若为真则课程存在 若为假则课程不存在 弹出提示对话框

/////////////////////////////CheckCourse测试成功/////////////////////
bool MainWindow::CheckCourse(QString tStr)
{
    QSqlQuery tQuery;
    QString tSearch=QString("select* from course");          //在数据库里全盘查询
    if(!tQuery.exec(tSearch))
    {
        qDebug()<<"Failed to Select in CheckCourse function";
    }
    else
    {
        while(tQuery.next())
        {
            if(tStr==tQuery.value("id").toString())
            {
                return true;
            }
        }
    }
    return false;
}

//将数据库里的课程对象数据呈递给学生向量中的课程数组
void MainWindow::AddIntoStudent(Student& tStu,QString tStr)
{
   QSqlQuery tQuery;
   QString tSearch=QString("select * from course");                 //遍历数据库查询id为tStr的数据
   if(!tQuery.exec(tSearch))
   {
       qDebug()<<"Failed to search in AddIntoStudent function";
   }
   else
   {
////////////////////////////////////////这一步执行到位了////////////////////////////////
       while(tQuery.next())
       {
           if(tQuery.value("id").toString()==tStr)                            //找到当前名为tStr的数据库成员 并将数据放到课程数组中
           {
               tStu.mCourse[tStu.miNum].msId=tQuery.value("id").toString();
               tStu.mCourse[tStu.miNum].msCourseName=tQuery.value("name").toString();
               tStu.mCourse[tStu.miNum].msTime=tQuery.value("timetable").toString();
               tStu.mCourse[tStu.miNum].micredit=tQuery.value("credit_num").toInt();
               tStu.mCourse[tStu.miNum].miSemester=tQuery.value("semester_num").toInt();
               tStu.mCourse[tStu.miNum].msClassroom=tQuery.value("classroom").toString();
           }
       }
   }
}

//在表格中展示当前学生的数据汇总
void MainWindow::ShowStudentsTable()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->tableWidget->setColumnCount(6);
    QStringList tHeader;
    tHeader<<"学号"<<"姓名"<<"班级"<<"电话"<<"生日"<<"地址";
    ui->tableWidget->setHorizontalHeaderLabels(tHeader);

    //设置行数为此时的学生数量
    ui->tableWidget->setRowCount(table.getTotalNum());
    //设置每一行的内容
    for(int i=0;i<table.getTotalNum();i++)
    {
            //从StudentTable中获取学生的信息
            QString tId=table.student_table[i].getId();
            QString tName=table.student_table[i].getName();
            QString tClass=table.student_table[i].getClass();
            QString tPhone=table.student_table[i].getPhone();
            QString tAddress=table.student_table[i].getAddress();
            QDate tBirthday=table.student_table[i].getBirthday();

            ui->tableWidget->setItem(i,0,new QTableWidgetItem(tId));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(tName));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(tClass));
            ui->tableWidget->setItem(i,3,new QTableWidgetItem(tPhone));
            //利用QDate里的toString函数将生日转化为字符串
            ui->tableWidget->setItem(i,4,new QTableWidgetItem(tBirthday.toString("yyyy'年'M'月'd'日'")));
            ui->tableWidget->setItem(i,5,new QTableWidgetItem(tAddress));
    }
}


//在表格中展示个人选课信息

//重载上述函数 方便点击“开始选课”后调用 不需要再次输入学号即可查询
void MainWindow::ShowStudentsCourse(Student& tStu)
{
    ui->stackedWidget->setCurrentIndex(3);

    //先把表格头展示在窗口
    ui->tableWidget_02->setColumnCount(6);
    QStringList tHeader;
    tHeader<<"课程编号"<<"课程名称"<<"课程时间"<<"学分数"<<"学期数"<<"上课地点";
    ui->tableWidget_02->setHorizontalHeaderLabels(tHeader);

    ui->tableWidget_02->setRowCount(tStu.miNum);

    //先将学生个人数据传入label
    ui->lineEdit_id01->setText(tStu.getId());
    ui->label_name->setText(tStu.getName());
    ui->label_class->setText(tStu.getClass());
    ui->label_phone->setText(tStu.getPhone());
    //利用QDate里的toString函数将生日转化为字符串
    ui->label_birthday->setText(tStu.getBirthday().toString("yyyy'年'M'月'd'日'"));
    ui->label_address->setText(tStu.getAddress());

    //将学生选的每一门课程信息传入表格
    for(int j=0;j<tStu.miNum;j++)
    {
        QString tId=tStu.mCourse[j].msId;
        QString tName=tStu.mCourse[j].msCourseName;
        QString tTime=tStu.mCourse[j].msTime;
        int tCredit=tStu.mCourse[j].micredit;
        int tSemester=tStu.mCourse[j].miSemester;
        QString tClassroom=tStu.mCourse[j].msClassroom;

        ui->tableWidget_02->setItem(j,0,new QTableWidgetItem(tId));
        ui->tableWidget_02->setItem(j,1,new QTableWidgetItem(tName));
        ui->tableWidget_02->setItem(j,2,new QTableWidgetItem(tTime));
        ui->tableWidget_02->setItem(j,3,new QTableWidgetItem(QString::number( tCredit)));
        ui->tableWidget_02->setItem(j,4,new QTableWidgetItem(QString::number(tSemester)));
        ui->tableWidget_02->setItem(j,5,new QTableWidgetItem(tClassroom));
    }
}

//展示特定课程的表格
void MainWindow::ShowSpecificClass()
{
    QString tStr=ui->lineEdit_idC->text();
    if(!CheckCourse(tStr))                        //用CheckCourse函数检测数据库中是否有名为tStr的课程
    {
        QMessageBox::information(this,"查询提示","不存在此课程");
    }
    else
    {
        int tnum=0;                               //用于记录有几位学生选择特定课程
        int tArr[20];                             //用一个数组 记录循环中有那几位学生选择特定课程
        for(int i=0;i<table.getTotalNum();i++)    //遍历学生的所有课程 查询是否有学生选择特定课程
        {
            for(int j=0;j<table.student_table[i].miNum;j++)
            {
                QString tStr_01=table.student_table[i].mCourse[j].msId;
                if(tStr==tStr_01)
                {
                    ui->label_nameC->setText(table.student_table[i].mCourse[j].msCourseName);
                    tArr[tnum]=i;
                    tnum++;
                }
            }
        }

        //先把表格头展示在窗口
        ui->tableWidget_4->setColumnCount(6);
        QStringList tHeader;
        tHeader<<"学号"<<"姓名"<<"班级"<<"电话"<<"生日"<<"地址";
        ui->tableWidget_4->setHorizontalHeaderLabels(tHeader);
        //打印表格的行数
        ui->tableWidget_4->setRowCount(tnum);

        for(int i=0;i<tnum;i++)
        {
            int tIndex=tArr[i];
            QString tId=table.student_table[tIndex].getId();
            QString tName=table.student_table[tIndex].getName();
            QString tClass=table.student_table[tIndex].getClass();
            QString tPhone=table.student_table[tIndex].getPhone();
            QString tAddress=table.student_table[tIndex].getAddress();
            QDate tBirthday=table.student_table[tIndex].getBirthday();

            ui->tableWidget_4->setItem(i,0,new QTableWidgetItem(tId));
            ui->tableWidget_4->setItem(i,1,new QTableWidgetItem(tName));
            ui->tableWidget_4->setItem(i,2,new QTableWidgetItem(tClass));
            ui->tableWidget_4->setItem(i,3,new QTableWidgetItem(tPhone));
            //利用QDate里的toString函数将生日转化为字符串
            ui->tableWidget_4->setItem(i,4,new QTableWidgetItem(tBirthday.toString("yyyy'年'M'月'd'日'")));
            ui->tableWidget_4->setItem(i,5,new QTableWidgetItem(tAddress));
        }
    }
}


//将数据初始化到user数据表中
void MainWindow::InsertDatatoUser()
{
    QSqlQuery tquery;
    QString tInsert_01=QString("insert into users (username,password)"
                               "values('JS322235','123456');");
    QString tInsert_02=QString("insert into users (username,password)"
                               "values('JS322236','123456');");
    QString tInsert_03=QString("insert into users (username,password)"
                               "values('JS322237','123456');");
    QString tInsert_04=QString("insert into users (username,password)"
                               "values('JS322238','123456');");
    QString tInsert_05=QString("insert into users (username,password)"
                               "values('JS322239','123456');");
    QString tInsert_06=QString("insert into users (username,password)"
                               "values('JS322240','123456');");
    QString tInsert_07=QString("insert into users (username,password)"
                               "values('JS322241','123456');");
    QString tInsert_08=QString("insert into users (username,password)"
                               "values('JS322242','123456');");
    QString tInsert_09=QString("insert into users (username,password)"
                               "values('JS322243','123456');");
    QString tInsert_10=QString("insert into users (username,password)"
                               "values('JS322244','123456');");

    tquery.exec(tInsert_01);
    tquery.exec(tInsert_02);
    tquery.exec(tInsert_03);
    tquery.exec(tInsert_04);
    tquery.exec(tInsert_05);
    tquery.exec(tInsert_06);
    tquery.exec(tInsert_07);
    tquery.exec(tInsert_08);
    tquery.exec(tInsert_09);
    tquery.exec(tInsert_10);
}

void MainWindow::LoginIn()
{
    QSqlQuery tquery;
    QString tselect=QString("select * from users");
    QString tManagerName=QString("Manager");                       //管理员的账号命名为Manager
    QString tManagerPassword=QString("123456789");                 //密码是          123456789
    if(!tquery.exec(tselect))
    {
        qDebug()<<"Failed to select users in LoginIn fuction"<<tquery.lastError();
    }

    else
    {
        //设置一个计数器 判断是否有这个账号
        int tcounter=0;
        while(tquery.next())
        {
            //登入学生端
            if(ui->lineEdit_username->text()==tquery.value("username").toString()&&    //如果用户名与密码都与数据库里的相同
                    ui->lineEdit_password->text()==tquery.value("password").toString())
            {
                mStatus=0;                 //表示现在是学生端
                ShowInfo();                //展示主页页面信息
                tcounter++;
                break;
            }
            //登入管理员端
            else if(ui->lineEdit_username->text()==tManagerName&&
                    ui->lineEdit_password->text()==tManagerPassword)
            {
                mStatus=1;                 //表示现在是管理员端
                tcounter++;
                QMessageBox::information(this,"欢迎！","热烈欢迎尊贵的管理员！");
                ui->stackedWidget->setCurrentIndex(0);
                ShowStudentsTable();
                break;
            }
        }
        //若没有这个账号  则提示下列信息
        if(tcounter==0)
        {
            QMessageBox::information(this,"登录提示","用户名或密码输入错误");
            ui->lineEdit_username->clear();
            ui->lineEdit_password->clear();
        }
    }
}

//展示当前登录学生的信息主页 需要遍历与取出
 void MainWindow::ShowInfo()
 {
     ui->stackedWidget->setCurrentIndex(4);  //将页面切换到主页页面
     for(int i=0;i<table.getTotalNum();i++)
     {
         if(ui->lineEdit_username->text()==table.student_table[i].getId())
         {

             ui->label_idx->setText(table.student_table[i].getId());
             ui->label_namex->setText(table.student_table[i].getName());
             ui->label_classx->setText(table.student_table[i].getClass());
             ui->label_phonex->setText(table.student_table[i].getPhone());
             ui->label_birthdayx->setText(table.student_table[i].getBirthday().toString("yyyy'年'M'月'd'日'"));
             ui->label_addressx->setText(table.student_table[i].getAddress());
         }
     }
 }


//先规划好JSON里的Jobject与Jarray的层次关系
/*
[
student01
  {
    Id 学号，
    Name 姓名，
    Class 班级，
    Phone 电话，
    Birthday 生日，
    Address 地址，
    [class01{Id 课程编号，Name 课程名称，TimeSchedual 课程时间，Credit_num 学分数，Semester_num 学期数，Classroom 课程教室}，
     class02,...,class0x]
  },
  ......
student0x
  {
   ......
  }
]

文字总结：
一个大数组，里面装若干学生对象，每个学生对象里包含若干数据成员，其中有一个课程数组，
数组内包含若干课程对象，每个课程对象中包含若干数据成员
*/

//将数据写入JSON文件中去
 void MainWindow::WriteJson()
 {
     QJsonArray tStudentTable;   //作为JSON结构的最外侧

     //对第i位学生 将其各个数据成员赋值到 JSON类的对象、数组及KEY值中去
     for(int i=0;i<table.getTotalNum();i++)
     {
         QJsonArray tClassTable; //作为单个学生中的课程列表数组
         QString tId_s=table.student_table[i].getId();
         QString tName_s=table.student_table[i].getName();
         QString tClass=table.student_table[i].getClass();
         QString tPhone=table.student_table[i].getPhone();
         QString tAddress=table.student_table[i].getAddress();

         QJsonObject tStudent;
         tStudent.insert("Id",tId_s);
         tStudent.insert("Name",tName_s);
         tStudent.insert("Class",tClass);
         tStudent.insert("Phone",tPhone);
         tStudent.insert("Address",tAddress);

         for(int j=0;j<table.student_table[i].miNum;j++)
         {
             QJsonObject tClass;
             QString tId_c=table.student_table[i].mCourse[j].msId;
             QString tName_c=table.student_table[i].mCourse[j].msCourseName;
             QString tTime_c=table.student_table[i].mCourse[j].msTime;
             int tCredit=table.student_table[i].mCourse[j].micredit;
             int tSemester=table.student_table[i].mCourse[j].miSemester;
             QString tClassroom_c=table.student_table[i].mCourse[j].msClassroom;

             //把学生中的第J个课程对象 赋值到 临时Json对象tClass中
             tClass.insert("Id",tId_c);
             tClass.insert("Name",tName_c);
             tClass.insert("TimeSchedual",tTime_c);
             tClass.insert("Credit_num",QString::number(tCredit));
             tClass.insert("Semester_num",QString::number(tSemester));
             tClass.insert("Classroom",tClassroom_c);

             //将该课程加入到课程列表当中去
             tClassTable.append(tClass);
         }
         //将课程列表insert到学生JSON类中
         tStudent.insert("ClassTable",tClassTable);
         tStudentTable.append(tStudent);
     }

     //准备将其写到JSON文件中去
     QJsonDocument tdoc(tStudentTable);
     //将其转化为JSON VALUE的形式
     QByteArray tarr= tdoc.toJson();

     //将tfile文件对象命名为下述地址 在D盘里面
     QFile tfile("D:\\Test.json");

     //打开文件方式是“只写”
     tfile.open(QFile::WriteOnly);
     tfile.write(tarr);
     tfile.close();
 }
