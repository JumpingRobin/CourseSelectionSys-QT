#ifndef STUDENTINFODIALOG_H
#define STUDENTINFODIALOG_H

#include <QDialog>
#include"listtable.h"


namespace Ui {
class StudentInfoDialog;
}

class StudentInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StudentInfoDialog(QWidget *parent = nullptr);
    ~StudentInfoDialog();

    //将ui中lineEdit里的内容利用函数传出本类
    QString getId();                        //获取学号
    QString getName();                      //获取姓名
    QString getClass();                     //获取班级
    QString getPhone();                     //获取电话
    QDate getBirthday();                    //获取生日
    QString getAddress();                   //获取地址

private slots:
    void on_btn_addA_clicked();

    void on_btn_deleteA_clicked();

private:
    Ui::StudentInfoDialog *ui;
};

#endif // STUDENTINFODIALOG_H
