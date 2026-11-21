QT       += core gui widgets multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cpps/Game_mode.cpp \
    cpps/character.cpp \
    cpps/enemy.cpp \
    cpps/main.cpp \
    cpps/main_ui.cpp \
    cpps/mainwindow.cpp \
    cpps/normal_mode.cpp \
    cpps/player.cpp \
    cpps/player1.cpp \
    cpps/weapon.cpp \
    cpps/weapon1.cpp

HEADERS += \
    heads/Game_mode.h \
    heads/character.h \
    heads/enemy.h \
    heads/main_ui.h \
    heads/mainwindow.h \
    heads/normal_mode.h \
    heads/player.h \
    heads/player1.h \
    heads/weapon.h \
    heads/weapon1.h

FORMS += \
    cpps/main_ui.ui \
    cpps/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    cpps/resource.qrc

DISTFILES += \
    Sprout Lands - Sprites - Basic pack/Sprout Lands - Sprites - Basic pack/Tilesets/Hills.png

STATECHARTS +=
