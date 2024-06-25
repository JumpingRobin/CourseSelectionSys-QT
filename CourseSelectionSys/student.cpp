#include "student.h"

Student::Student()
{
    miNum=0;  //将学生的选课数量初始化为0
}

//拷贝构造函数
Student::Student(const Student&tstu)
{
    this->msId=tstu.msId;
    this->msName=tstu.msName;
    this->msClass=tstu.msClass;
    this->mdBirthday=tstu.mdBirthday;
    this->msAddress=tstu.msAddress;
    this->msPhone=tstu.msPhone;

    for(int i=0;i<tstu.miNum;i++)
    {
        this->mCourse[i]=tstu.mCourse[i];
    }
    this->miNum=tstu.miNum;
}

//重载等号运算符
Student& Student::operator= (const Student& tstu)
{
    this->msId=tstu.msId;
    this->msName=tstu.msName;
    this->msClass=tstu.msClass;
    this->mdBirthday=tstu.mdBirthday;
    this->msAddress=tstu.msAddress;
    this->msPhone=tstu.msPhone;

    for(int i=0;i<tstu.miNum;i++)
    {
        this->mCourse[i]=tstu.mCourse[i];
    }
    this->miNum=tstu.miNum;
    return *this;
}

//将Student里的数据保存在数据流中里去
void Student::SaveStudent(QTextStream &tStream)
{
    tStream<<msId<<'\n';
    tStream<<msName<<'\n';
    tStream<<msClass<<'\n';
    tStream<<msPhone<<'\n';
    tStream<<mdBirthday.year()<<" "<<mdBirthday.month()<<" "<<mdBirthday.day()<<'\n';
    tStream<<msAddress<<'\n';
    tStream<<miNum<<'\n';                //保存学生的选课数量
                                         //否则 在读取文件时minum已经清零了 会导致将课程数据读取到学生数据处

    for(int i=0;i<miNum;i++)
    {
        tStream<<mCourse[i].msId<<'\n';
        tStream<<mCourse[i].msCourseName<<'\n';
        tStream<<mCourse[i].msTime<<'\n';
        tStream<<mCourse[i].micredit<<'\n';
        tStream<<mCourse[i].miSemester<<'\n';
        tStream<<mCourse[i].msClassroom<<'\n';
    }
}

//将文件流里的数据读入Student的对象数据成员中去
void Student::ReadStudent(QTextStream &tStream)
{
    tStream>>msId;
    tStream>>msName;
    tStream>>msClass;
    tStream>>msPhone;
    int year, month, day;
    tStream>>year>>month>>day;
    mdBirthday.setDate(year,month,day);
    tStream>>msAddress;
    tStream>>miNum;


    for(int i=0;i<miNum;i++)
    {
        tStream>>mCourse[i].msId;
        tStream>>mCourse[i].msCourseName;
        tStream>>mCourse[i].msTime;
        tStream>>mCourse[i].micredit;
        tStream>>mCourse[i].miSemester;
        tStream>>mCourse[i].msClassroom;
    }
}


//设置set接口，方便赋值
void Student::setId(QString tstr)
{
    this->msId=tstr;
}

void Student::setName(QString tstr)
{
    this->msName=tstr;
}

void Student::setClass(QString tstr)
{
    this->msClass=tstr;
}

void Student::setPhone(QString tstr)
{
    this->msPhone=tstr;
}

void Student::setBirthday(QDate tday)
{
    this->mdBirthday=tday;
}

void Student::setAddress(QString tstr)
{
    this->msAddress=tstr;
}

//设置get接口 获取类中的数据
QString Student::getId()
{
   return msId;
}

QString Student::getName()
{
    return msName;
}

QString Student::getClass()
{
    return msClass;
}

QString Student::getPhone()
{
    return msPhone;
}

QString Student::getAddress()
{
    return msAddress;
}

QDate Student::getBirthday()
{
    return mdBirthday;
}




