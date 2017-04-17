#-------------------------------------------------
#
# Project created by QtCreator 2017-04-01T10:46:55
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = card_game
TEMPLATE = app

#mingw32 make 编译问题, 不用预编译头
PRECOMPILED_HEADER = pch.h

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../common/card/card.pri)
include(../common/network/network.pri)

SOURCES += main.cpp\
    card_item.cpp \
    cardchooser.cpp \
    comparehandinfowidget.cpp \
    handinfowidget.cpp \
    item_rect.cpp \
    static_cardimage.cpp \
    testhandinfowidget.cpp


HEADERS  += \
    card_item.h \
    cardchooser.h \
    comparehandinfowidget.h \
    handinfowidget.h \
    item_rect.h \
    static_cardimage.h \
    testhandinfowidget.h


RESOURCES += \
    res_cards.qrc
