#-------------------------------------------------
#
# Project created by QtCreator 2017-04-01T10:46:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = card_game
TEMPLATE = app

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
        widget.cpp \
    card.cpp \
    card_compare.cpp \
    card_iter.cpp \
    card_deck.cpp \
    image_deck.cpp \
    onehand.cpp \
    hand_helper.cpp

HEADERS  += widget.h \
    card_color.h \
    card_value.h \
    card.h \
    card_compare.h \
    card_iter.h \
    card_deck.h \
    init_deck.h \
    image_deck.h \
    onehand.h \
    hand_type.h \
    hand_helper.h

RESOURCES += \
    res_cards.qrc
