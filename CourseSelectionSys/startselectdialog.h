#ifndef STARTSELECTDIALOG_H
#define STARTSELECTDIALOG_H

#include <QDialog>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlError>
#include<QDebug>
#include<QString>

namespace Ui {
class StartSelectDialog;
}

class StartSelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StartSelectDialog(QWidget *parent = nullptr);
    ~StartSelectDialog();
    void select_table();
    QString getSelectId();              //获取ui中的lineEdit_id内容      即课程编号
    QString getSelectIdOfStudent();     //获取ui中的lineEdit_id_03的内容  即学生学号

private slots:
    void on_btn_add_clicked();

    void on_btn_delete_clicked();

private:
    Ui::StartSelectDialog *ui;

};

#endif // STARTSELECTDIALOG_H
