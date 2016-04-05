TEMPLATE = app

QT += qml quick serialport sql

CONFIG += c++11

SOURCES += main.cpp \
    serialhandler.cpp \
    match.cpp \
    maincontroller.cpp \
    storagecontroller.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    serialhandler.h \
    match.h \
    maincontroller.h \
    storagecontroller.h
