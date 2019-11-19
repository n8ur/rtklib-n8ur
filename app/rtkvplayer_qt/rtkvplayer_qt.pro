#-------------------------------------------------
#
# Project created by QtCreator 2016-01-30T18:29:59
#
#-------------------------------------------------

QT       += widgets core gui multimedia multimediawidgets

include(../app.pri)

TARGET = rtkvplayer_qt
TEMPLATE = app

INCLUDEPATH += ../../src/ ../appcmn_qt

SOURCES += \
#    mjpgplayer.cpp \
    vplayermain.cpp \ 
    rtkvplayer.cpp \
    vpoptdlg.cpp

HEADERS  += \
    vplayermain.h \
    vpoptdlg.h
    #mjpgplayer.h

FORMS    += \
    vplayermain.ui \ 
    vpoptdlg.ui

RESOURCES += \
    rtkvplayer_qt.qrc

#RC_FILE = rtkvplayer_qt.rc
