QT       += core gui network xml

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
    genpasswidget.cpp \
    graphicgenerator.cpp \
    hashmanager.cpp \
    hashmodepanel.cpp \
    idlepanel.cpp \
    main.cpp \
    mainwindow.cpp \
    newpassrecord.cpp \
    passmngrpanel.cpp \
    passmngrsettings.cpp \
    passmngrstorage.cpp \
    passrecord.cpp \
    passwordgeneratordialog.cpp \
    signmanager.cpp \
    signmodepanel.cpp \
    storagemngr.cpp \
    textmodepanel.cpp \
    yandexmodepanel.cpp

HEADERS += \
    cryptmanager.h \
    filemodepanel.h \
    genpasswidget.h \
    graphicgenerator.h \
    hashmanager.h \
    hashmodepanel.h \
    idlepanel.h \
    mainwindow.h \
    newpassrecord.h \
    passmngrpanel.h \
    passmngrsettings.h \
    passmngrstorage.h \
    passrecord.h \
    passwordgeneratordialog.h \
    signmanager.h \
    signmodepanel.h \
    storagemngr.h \
    textmodepanel.h \
    yandexmodepanel.h

FORMS += \
    filemodepanel.ui \
    genpasswidget.ui \
    hashmodepanel.ui \
    idlepanel.ui \
    mainwindow.ui \
    newpassrecord.ui \
    passmngrpanel.ui \
    passmngrsettings.ui \
    passmngrstorage.ui \
    passwordgeneratordialog.ui \
    signmodepanel.ui \
    textmodepanel.ui \
    yandexmodepanel.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Icons.qrc
