#ifndef STUDENTINFO_H
#define STUDENTINFO_H

#include <QWidget>

namespace Ui {
class StudentInfo;
}

class StudentInfo : public QWidget
{
    Q_OBJECT

public:
    explicit StudentInfo(QWidget *parent = nullptr);
    ~StudentInfo();

private:
    Ui::StudentInfo *ui;
};

#endif // STUDENTINFO_H
