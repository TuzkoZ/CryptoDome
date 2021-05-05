QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

INCLUDEPATH += "E:\Programming\Libs\CryptoPP"
LIBS += E:\Programming\Libs\CryptoPP\Win32\Output\Release\cryptlib.lib

QMAKE_CXXFLAGS_DEBUG += /MTd
QMAKE_CXXFLAGS_RELEASE += /MT

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cryptmanager.cpp \
    filemodepanel.cpp \
    hashmanager.cpp \
    hashmodepanel.cpp \
    idlepanel.cpp \
    main.cpp \
    mainwindow.cpp \
    signmanager.cpp \
    signmodepanel.cpp \
    textmodepanel.cpp

HEADERS += \
    cryptmanager.h \
    filemodepanel.h \
    hashmanager.h \
    hashmodepanel.h \
    idlepanel.h \
    mainwindow.h \
    signmanager.h \
    signmodepanel.h \
    textmodepanel.h

FORMS += \
    filemodepanel.ui \
    hashmodepanel.ui \
    idlepanel.ui \
    mainwindow.ui \
    signmodepanel.ui \
    textmodepanel.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Icons.qrc
