#ifndef LISTTABLE_H
#define LISTTABLE_H

#include <QWidget>

namespace Ui {
class ListTable;
}

class ListTable : public QWidget
{
    Q_OBJECT

public:
    explicit ListTable(QWidget *parent = nullptr);
    ~ListTable();
    void setTableInfo(QString tId,QString tName,QString tTimetable, int tcredit,int tsemester,QString tclassroom);
private:
    Ui::ListTable *ui;
};

#endif // LISTTABLE_H
