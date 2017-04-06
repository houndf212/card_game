#-------------------------------------------------
#
# Project created by QtCreator 2017-04-01T10:46:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = card_game
TEMPLATE = app

#mingw32 make 编译问题, 不用预编译头
#PRECOMPILED_HEADER = pch.h

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    card.cpp \
    card_compare.cpp \
    static_deck.cpp \
    static_cardimage.cpp \
    deck.cpp \
    card_item.cpp \
    hand_info.cpp \
    deck_rect.cpp \
    item_rect.cpp \
    cardchooser.cpp \
    handinfowidget.cpp \
    testhandinfowidget.cpp \
    comparehandinfowidget.cpp \
    hand_hinter.cpp \
    hand_helper.cpp \
    hand_hinter_a.cpp

HEADERS  += \
    card.h \
    card_compare.h \
    static_deck.h \
    static_cardimage.h \
    deck.h \
    card_item.h \
    pch.h \
    hand_info.h \
    deck_rect.h \
    item_rect.h \
    cardchooser.h \
    handinfowidget.h \
    testhandinfowidget.h \
    comparehandinfowidget.h \
    hand_hinter.h \
    hand_helper.h \
    hand_hinter_a.h

RESOURCES += \
    res_cards.qrc
