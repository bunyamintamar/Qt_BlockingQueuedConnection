QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

SOURCES += \
        MainThread.cpp \
        SecondThread.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    MainThread.h \
    SecondThread.h
