QT       += core gui

QT       += core gui charts

QT       += core gui serialport
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CRC8.cpp \
    connection.cpp \
    main.cpp \
    mainwindow.cpp \
    mapped_path.cpp \
    sensor_state.cpp \
    wheel_speed1.cpp

HEADERS += \
    CRC8.h \
    connection.h \
    mainwindow.h \
    mapped_path.h \
    sensor_state.h \
    wheel_speed1.h

FORMS += \
    connection.ui \
    mainwindow.ui \
    mapped_path.ui \
    sensor_state.ui \
    wheel_speed1.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
