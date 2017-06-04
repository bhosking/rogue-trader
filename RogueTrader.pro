QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = RogueTrader

TEMPLATE = app

SOURCES += main.cpp \
    resource.cpp \
    config.cpp \
    townresource.cpp \
    town.cpp \
    carriedresource.cpp \
    mainwindow.cpp \
    player.cpp \
    map.cpp \
    world.cpp \
    worldscene.cpp \
    playersceneitem.cpp \
    townsceneitem.cpp \
    circularsceneitem.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    resource.h \
    config.h \
    townresource.h \
    updatableentity.h \
    town.h \
    carriedresource.h \
    mainwindow.h \
    player.h \
    map.h \
    world.h \
    worldscene.h \
    playersceneitem.h \
    townsceneitem.h \
    circularsceneitem.h
