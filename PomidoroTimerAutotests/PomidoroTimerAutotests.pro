QT += testlib widgets
#QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_test.cpp \
    ../utility.cpp \
    ../pomidoro.cpp \
    ../state.cpp \
    ../concretestates.cpp

HEADERS += \
    ../utility.h \
    ../pomidoro.h \
    ../state.h \
    ../concretestates.cpp
