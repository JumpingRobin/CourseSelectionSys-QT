#ifndef STUDENTTABLE_H
#define STUDENTTABLE_H
#include"student.h"
#include<QVector>
#include<vector>
#include<QFile>

class StudentTable
{
public:
    StudentTable();
    void AddStudent(Student&);                        //添加学生函数  利用pushback 将该学生加到Vector的末尾
    void DeleteStudent(int);                          //删除学生函数  利用remove   将int对应的学生删除掉
    bool SaveTabletoFile(const QString &);            //保存为文件函数 利用Student类里的 SaveStudent函数 将Table里的学生遍历并保存在文件中
    bool ReadFile(const QString &);                   //读取txt文件

    Student& getCurStudent(int);                      //返回当前int数字编号下的学生
    int getTotalNum();                                //返回学生的总数mnum
    QVector<Student>student_table;                    //学生的向量
private:
    int mnum;                                         //mnum记录学生的总数
};

#endif // STUDENTTABLE_H
