#include "studenttable.h"
#include<QFile>
#include<QDebug>
#include<QTextCodec>

////////这个类存储学生的信息//////////
///添加一条学生记录后存储在此table里///
StudentTable::StudentTable()
{
    //学生类的属性
    //QString  msId;           //学号
    //QString  msName;         //姓名
    //QString  msClass;        //班级
    //QString  msPhone;        //电话
    //QDate    mdBirthday;     //生日
    //QString  msAddress;      //地址

    //ClassInfo mCourse[5];    //还需要一个类记录该学生的选课集合  ClassInfo类记录课程信息
    //int       miNum;         //记录学生选课的数量

    //构造函数中 将学生总数一开始初始化为0
    mnum=0;
}

//添加学生函数 pushback 将该学生加到Vector的末尾
//学生数加一
void StudentTable::AddStudent(Student &tStu)
{
    student_table.push_back(tStu);
    mnum++;
}

//删除学生函数 将对应的学生删除
//学生数顺势减一
void StudentTable::DeleteStudent(int ti)
{
    if(mnum>0)
    {
        student_table.remove(ti);
        mnum--;
    }
}

bool StudentTable::SaveTabletoFile(const QString &tFileName)
{
    QFile tFile(tFileName);                        //创建一个名叫 tFileName 的文件
                                                   //方便存储时用户对它取名

    //文件打开方式是只写 与 文本
    if(!tFile.open(QIODevice::WriteOnly| QIODevice::Text))
    {
        return false;
    }
    QTextStream tStream(&tFile);                          //用文本流操作文件指针
    tStream.setCodec(QTextCodec::codecForName("system")); //显示汉字

    tStream<<mnum<<'\n';                                  //写入学生总数
    if(mnum!=0)
    {
        for(int i=0;i<mnum;i++)
        {
            student_table[i].SaveStudent(tStream);
        }
    }

    //关闭文件
    tFile.close();
    //bool类型的函数 返回真值
    return true;
}

//将信息从文件里读取出来
bool StudentTable::ReadFile(const QString &tFileName)
{
    QFile tFile(tFileName);        //创建一个名叫 tFileName 的文件
                                   //方便打开文件时用户对它取名

    if(!tFile.exists())                                    //文件不存在
    {
        return false;
    }
    if(!tFile.open(QIODevice::ReadOnly | QIODevice::Text)) //以文本方式打开
    {
        return false;
    }
    QTextStream tStream(&tFile);                          //用文本流读取文件
    tStream.setCodec(QTextCodec::codecForName("system")); //显示汉字

    //先对向量与学生总数初始化 防止发生奇怪的事
    mnum=0;
    student_table.clear();

    //读取信息
    tStream>>mnum;
    Student tStu;                                    //创建一个临时对象 将文件里的内容输入到此对象中
    if(mnum>0)                                       //并将这个对象怼入student_table向量中pushback
    {
        for(int i=0;i<mnum;i++)
        {
            tStu.ReadStudent(tStream);
            student_table.push_back(tStu);
        }
    }

    tFile.close();
    return true;
}

//返回当前int数字编号下的学生
Student& StudentTable::getCurStudent(int ti)
{
    return student_table[ti];
}

//返回学生的总数
int StudentTable::getTotalNum()
{
    return mnum;
}


