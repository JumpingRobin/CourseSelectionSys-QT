#include "listtable.h"
#include "ui_listtable.h"

ListTable::ListTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListTable)
{
    ui->setupUi(this);
}

ListTable::~ListTable()
{
    delete ui;
}

//函数将形参里的内容输入到灰色label中去
//封装在ListTable类中方便各个界面类调用
void ListTable::setTableInfo(QString tId,QString tName,QString tTimetable,
                             int tCredit,int tSemester,QString tClassroom)
{
    ui->label_id->setText(tId);
    ui->label_name->setText(tName);
    ui->label_timeschedual->setText(tTimetable);
    ui->label_credit->setText(QString::number(tCredit));
    ui->label_semester->setText(QString::number(tSemester));
    ui->label_classroom->setText(tClassroom);
}

