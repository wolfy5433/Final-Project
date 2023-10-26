QT = core gui network

#QT += core network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        banusers.cpp \
        formusers.cpp \
        main.cpp \
        mainwindow.cpp \
        server.cpp


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    banusers.h \
    formusers.h \
    mainwindow.h \
    server.h


win32: LIBS += -L$$PWD/'../../../../../Program Files/MySQL/MySQL Server 8.0/lib/' -llibmysql

INCLUDEPATH += $$PWD/'../../../../../Program Files/MySQL/MySQL Server 8.0/include'
DEPENDPATH += $$PWD/'../../../../../Program Files/MySQL/MySQL Server 8.0/include'

FORMS += \
    banusers.ui \
    formusers.ui \
    mainwindow.ui
