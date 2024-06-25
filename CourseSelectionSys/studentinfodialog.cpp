#include "studentinfodialog.h"
#include "ui_studentinfodialog.h"

StudentInfoDialog::StudentInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentInfoDialog)
{
    ui->setupUi(this);
    setWindowTitle("添加学生信息");
}

StudentInfoDialog::~StudentInfoDialog()
{
    delete ui;
}

QString StudentInfoDialog::getId()
{
    return ui->lineEdit_id->text();
}

QString StudentInfoDialog::getName()
{
    return ui->lineEdit_name->text();
}

QString StudentInfoDialog::getClass()
{
    return ui->lineEdit_class->text();
}

QString StudentInfoDialog::getPhone()
{
    return ui->lineEdit_phone->text();
}

QString StudentInfoDialog::getAddress()
{
    return ui->lineEdit_address->text();
}

QDate StudentInfoDialog::getBirthday()
{
    return ui->dateEdit->date();
}

void StudentInfoDialog::on_btn_addA_clicked()
{
    accept();
}

void StudentInfoDialog::on_btn_deleteA_clicked()
{
    reject();
}
