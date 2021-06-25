#-------------------------------------------------
#
# Project created by QtCreator 2021-06-17T10:47:35
#
#-------------------------------------------------

QT       += core gui sql network axcontainer


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = APP
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11 #console

SOURCES += \
        Camera.cpp \
        Common.cpp \
        Configure/Configure.cpp \
        Configure/UI/ConfigureGlobal.cpp \
        Configure/UI/ConfigureUI.cpp \
        Log.cpp \
        PLC.cpp \
        Test/TestDrop.cpp \
        Test/UI/TestUI.cpp \
        Test/UI/ToolUI.cpp \
        Work/UI/ArrivedSendBagUI.cpp \
        Work/UI/CalculateSortDataUI.cpp \
        Work/UI/SortArrivedSendBag.cpp \
        Work/UI/SortDataShowUI.cpp \
        Work/UI/SortUI.cpp \
        main.cpp \
        MainWindow.cpp

HEADERS += \
        Camera.h \
        Common.h \
        Include/TcAdsAPI.h \
        Include/TcAdsDef.h \
        Configure/Configure.h \
        Configure/UI/ConfigureGlobal.h \
        Configure/UI/ConfigureUI.h \
        Log.h \
        MainWindow.h \
        PLC.h \
        Test/TestDrop.h \
        Test/UI/TestUI.h \
        Test/UI/ToolUI.h \
        Work/UI/ArrivedSendBagUI.h \
        Work/UI/CalculateSortDataUI.h \
        Work/UI/SortArrivedSendBag.h \
        Work/UI/SortDataShowUI.h \
        Work/UI/SortUI.h \
        define.h

FORMS += \
        MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32: LIBS += -LC:/TwinCAT/AdsApi/TcAdsDll/Lib/ -lTcAdsDll

INCLUDEPATH += C:/TwinCAT/AdsApi/TcAdsDll/Lib
DEPENDPATH += C:/TwinCAT/AdsApi/TcAdsDll/Lib
# 注意twincat库的位数

RC_FILE +=  logo.rc

RESOURCES += \
    resources.qrc

DISTFILES += \
    image/logo.ico
