#-------------------------------------------------
#
# Project created by QtCreator 2016-07-21T13:21:39
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = csgo_stats
TEMPLATE = app


SOURCES += main.cpp\
        user_select_dialog.cpp \
    file_download.cpp \
    stats_display_window.cpp \
    parse_file.cpp

HEADERS  += user_select_dialog.h \
    file_download.h \
    stats_display_window.h \
    parse_file.h

FORMS    += user_select_dialog.ui \
    stats_display_window.ui

RESOURCES += \
    csgo_images.qrc
