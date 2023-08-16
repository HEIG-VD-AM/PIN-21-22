QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    canvas.cpp \
    canvashelper.cpp \
    robot.cpp

HEADERS += \
    include/position.h \
    include/json.h \
    include/mainwindow.h \
    include/particle.h \
    include/robot.h \
    include/state.h \
    include/canvas.h \
    include/canvashelper.h \
    include/timeline.h \
    include/utility.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
