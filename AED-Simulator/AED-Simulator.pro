QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Safety.cpp \
    Simulations.cpp \
    aed.cpp \
    main.cpp \
    mainwindow.cpp \
    operations.cpp \
    prompt.cpp \
    timer.cpp \
    victim.cpp

HEADERS += \
    Safety.h \
    Simulations.h \
    aed.h \
    mainwindow.h \
    operations.h \
    prompt.h \
    timer.h \
    victim.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    images/afib.jpeg \
    images/check.png \
    images/grayed_out_check.png \
    images/grayed_out_x.png \
    images/normal.png \
    images/vfib.jpeg \
    images/vtach.jpeg \
    images/x.png

RESOURCES += \
    resources.qrc \
    resources.qrc
