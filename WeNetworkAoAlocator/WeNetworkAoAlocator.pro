QT       += core gui network mqtt

greaterThan(QT_MAJOR_VERSION, 4) QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    asset.cpp \
    assetsdetected.cpp \
    code_distance.cpp \
    database.cpp \
    dialogaddlocator.cpp \
    dialoginfos.cpp \
    dialogmodifylocator.cpp \
    dialogoptions.cpp \
    jsonparser.cpp \
    locator.cpp \
    main.cpp \
    mainwindow.cpp \
    refreshthread.cpp
    #mqttsubscriberclient.cpp

HEADERS += \
    asset.h \
    assetsdetected.h \
    code_distance.h \
    database.h \
    dialogaddlocator.h \
    dialoginfos.h \
    dialogmodifylocator.h \
    dialogoptions.h \
    jsonparser.h \
    locator.h \
    mainwindow.h \
    refreshthread.h
    #mqttsubscriberclient.h

FORMS += \
    dialogaddlocator.ui \
    dialoginfos.ui \
    dialogmodifylocator.ui \
    dialogoptions.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=
