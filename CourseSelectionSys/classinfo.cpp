#include "classinfo.h"

ClassInfo::ClassInfo()
{
}

//重载等号运算符
ClassInfo& ClassInfo::operator= (const ClassInfo& tClass)
{
    this->msId=tClass.msId;
    this->msCourseName=tClass.msCourseName;
    this->msTime=tClass.msTime;
    this->micredit=tClass.micredit;
    this->miSemester=tClass.miSemester;
    this->msClassroom=tClass.msClassroom;
    return *this;
}
