#-------------------------------------------------
#
# Project created by QtCreator 2019-01-31T20:06:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FastFoodFinder

TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the [ WTF BROOO] following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14


HEADERS += \
    src/windows/login.hpp \
    src/windows/mainwindow.hpp \
    src/windows/navitem.hpp \
    src/utils/exceptions.hpp \
    src/windows/navbar.hpp


SOURCES += \
    src/main.cpp \
    src/windows/login.cpp \
    src/windows/mainwindow.cpp \
    src/windows/navitem.cpp \
    src/utils/exceptions.cpp \
    src/windows/navbar.cpp

FORMS += \
    src/windows/login.ui \
    src/windows/mainwindow.ui \
    src/windows/navitem.ui \
    src/windows/navbar.ui

RESOURCES += \
    res.qrc \
    assets.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
