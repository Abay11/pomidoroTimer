QT += testlib widgets multimedia
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_test.cpp \
    ../datasaver.cpp \
    ../statesholder.cpp \
    ../utility.cpp \
    ../pomidoro.cpp \
    ../state.cpp \
    ../concretestates.cpp \
    ../threadcontroller.cpp

HEADERS += \
    ../datasaver.h \
    ../statesholder.h \
    ../utility.h \
    ../pomidoro.h \
    ../state.h \
    ../concretestates.cpp \
    ../threadcontroller.h
