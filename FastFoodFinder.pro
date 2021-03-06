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
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14


HEADERS += \
    src/utils/exceptions.hpp \
    src/windows/login.hpp \
    src/windows/mainwindow.hpp \
    src/widgets/navbar.hpp \
    src/widgets/navitem.hpp \
    src/widgets/restaurantlist.hpp \
    src/widgets/menulist.hpp \
    src/widgets/menulistitem.hpp \
    src/views/adminview.hpp \
    src/datastore/MyDblLinkList.hpp \
    src/datastore/Restaurant.hpp \
    src/datastore/MenuItem.hpp \
    src/datastore/RestaurantDataStore.hpp \
    src/datastore/Trip.hpp \
    src/datastore/TripDataStore.hpp \
    src/datastore/User.hpp \
    src/datastore/UserDataStore.hpp \
    src/views/restaurantsview.hpp \
    src/widgets/plantrip.hpp \
    src/widgets/receiptlist.hpp \
    src/widgets/receipt.hpp


SOURCES += \
    src/main.cpp \
    src/utils/exceptions.cpp \
    src/windows/login.cpp \
    src/windows/mainwindow.cpp \
    src/widgets/navbar.cpp \
    src/widgets/navitem.cpp \
    src/widgets/restaurantlist.cpp \
    src/widgets/menulist.cpp \
    src/widgets/menulistitem.cpp \
    src/views/adminview.cpp \
    src/datastore/Restaurant.cpp \
    src/datastore/MenuItem.cpp \
    src/datastore/RestaurantDataStore.cpp \
    src/datastore/Trip.cpp \
    src/datastore/TripDataStore.cpp \
    src/datastore/User.cpp \
    src/datastore/UserDataStore.cpp \
    src/views/restaurantsview.cpp \
    src/widgets/plantrip.cpp \
    src/widgets/receiptlist.cpp \
    src/widgets/receipt.cpp

FORMS += \
    src/windows/login.ui \
    src/windows/mainwindow.ui \
    src/widgets/navitem.ui \
    src/widgets/menulistitem.ui \
    src/views/adminview.ui \
    src/views/restaurantsview.ui \
    src/widgets/plantrip.ui \
    src/widgets/receipt.ui

RESOURCES += \
    res.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
