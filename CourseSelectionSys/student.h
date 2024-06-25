#ifndef STUDENT_H
#define STUDENT_H
#include<QString>
#include<QDate>
#include <QTextStream>
#include"classinfo.h"

class Student
{
public:
    Student();
    Student(const Student&);                                //拷贝构造函数
    Student& operator= (const Student& tStu);               //重载等号运算符
    void SaveStudent(QTextStream &);                        //将Student里的数据保存在文件里去
    void ReadStudent(QTextStream &);                        //将文件里的数据读入Student的对象数据成员中去

    void setId(QString);
    void setName(QString);
    void setClass(QString);
    void setPhone(QString);
    void setBirthday(QDate);
    void setAddress(QString);

    QString getId();
    QString getName();
    QString getClass();
    QString getPhone();
    QDate getBirthday();
    QString getAddress();

    ClassInfo mCourse[5];     //还需要一个类记录该学生的选课集合  ClassInfo类记录课程信息
    int       miNum;          //记录学生选课的数量
private:
    //属性：member 类型：Qstring  ms_...命名
    QString  msId;           //学号
    QString  msName;         //姓名
    QString  msClass;        //班级
    QString  msPhone;        //电话
    QDate    mdBirthday;     //生日
    QString  msAddress;      //地址
};


#endif // STUDENT_H
