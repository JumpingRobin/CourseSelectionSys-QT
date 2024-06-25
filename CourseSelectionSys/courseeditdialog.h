#ifndef COURSEEDITDIALOG_H
#define COURSEEDITDIALOG_H

#include <QDialog>
#include"listtable.h"
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlError>
#include<QDebug>
#include"listtable.h"

namespace Ui {
class CourseEditDialog;
}

class CourseEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CourseEditDialog(QWidget *parent = nullptr);
    ~CourseEditDialog();
    void select_table(); //对数据库重新遍历 更新listTable
    void renew();        //更新函数：将lineEdit里内容清空 并在listTable进行刷新

private slots:
    void on_btn_delete_clicked();

    void on_btn_add_clicked();

    void on_btn_modify_clicked();

private:
    Ui::CourseEditDialog *ui;
};

#endif // COURSEEDITDIALOG_H
