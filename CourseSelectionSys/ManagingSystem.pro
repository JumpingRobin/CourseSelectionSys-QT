QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    classinfo.cpp \
    courseeditdialog.cpp \
    listtable.cpp \
    main.cpp \
    mainwindow.cpp \
    startselectdialog.cpp \
    student.cpp \
    studentinfodialog.cpp \
    studenttable.cpp

HEADERS += \
    classinfo.h \
    courseeditdialog.h \
    listtable.h \
    mainwindow.h \
    startselectdialog.h \
    student.h \
    studentinfodialog.h \
    studenttable.h

FORMS += \
    courseeditdialog.ui \
    listtable.ui \
    mainwindow.ui \
    startselectdialog.ui \
    studentinfodialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
