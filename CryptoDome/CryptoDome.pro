QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

INCLUDEPATH += "D:\Tools\Libraries\cryptopp"
LIBS += D:\Tools\Libraries\cryptopp\Win32\Output\Release\cryptlib.lib

QMAKE_CXXFLAGS_DEBUG += /MTd
QMAKE_CXXFLAGS_RELEASE += /MT

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    filemodepanel.cpp \
    hashmanager.cpp \
    hashmodepanel.cpp \
    main.cpp \
    mainwindow.cpp \
    signmanager.cpp \
    signmodepanel.cpp \
    textmodepanel.cpp

HEADERS += \
    filemodepanel.h \
    hashmanager.h \
    hashmodepanel.h \
    mainwindow.h \
    signmanager.h \
    signmodepanel.h \
    textmodepanel.h

FORMS += \
    filemodepanel.ui \
    hashmodepanel.ui \
    mainwindow.ui \
    signmodepanel.ui \
    textmodepanel.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Icons.qrc