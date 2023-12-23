QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Course.cpp \
    Homework.cpp \
    Remind.cpp \
    fix.cpp \
    fixcs.cpp \
    fixre.cpp \
    game.cpp \
    login.cpp \
    main.cpp \
    notice.cpp \
    user.cpp \
    widget.cpp \
    wrong.cpp

HEADERS += \
    Course.h \
    Homework.h \
    MemoInfo.hpp \
    Remind.h \
    fix.h \
    fixcs.h \
    fixre.h \
    game.h \
    login.h \
    notice.h \
    user.h \
    widget.h \
    wrong.h

FORMS += \
    fix.ui \
    fixcs.ui \
    fixre.ui \
    game.ui \
    login.ui \
    notice.ui \
    widget.ui \
    wrong.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Memo-resource.qrc



