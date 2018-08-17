#-------------------------------------------------
#
# Project created by QtCreator 2018-08-14T18:06:18
#
#-------------------------------------------------

QT       += widgets

TARGET = MPDcontroller
TEMPLATE = lib
CONFIG  += plugin c++11 link_pkgconfig

PKGCONFIG += libmpd


# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        ddedockmpdplugin.cpp \
    ddedockmpdwidget.cpp \
    iconlabel.cpp \
    mpdinterface.cpp \
    marqueewidget.cpp \
    tipswidget.cpp

HEADERS += \
        ddedockmpdplugin.h \
    ddedockmpdwidget.h \
    iconlabel.h \
    mpdinterface.h \
    mpd_global.h \
    marqueewidget.h \
    tipswidget.h

DISTFILES += \
    dde-dock-mpd.json

isEmpty(PREFIX) {
    PREFIX = /usr
}

target.path = $${PREFIX}/lib/dde-dock/plugins/
INSTALLS += target

RESOURCES += \
    res.qrc

TRANSLATIONS = dde-dock-mpd_zh_CN.ts \
                dde-dock-mpd_en.ts
