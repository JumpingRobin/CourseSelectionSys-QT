#ifndef CLASSINFO_H
#define CLASSINFO_H
#include <QString>

///////////////这个类表示一门单独的课程信息///////////////
/////////////////封装在这一个类中比较方便////////////////

class ClassInfo
{
public:
    ClassInfo();
    QString msId;            //课程编号
    QString msCourseName;    //课程名称
    QString msTime;          //时间
    int micredit;            //学分数
    int miSemester;          //学期数
    QString msClassroom;     //教室

    ClassInfo& operator= (const ClassInfo& tClass);  //重载等号运算符
};

#endif // CLASSINFO_H
