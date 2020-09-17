CONFIG += debug_and_release
TARGET = EvoApp_QmlDemo
TEMPLATE = lib
QT += qml quick gui core

include($$PWD/../../EVO.pri)
DESTDIR = $$DESTDIR_LIB
LIBS += -lEvoLog -lEvoUI

HEADERS += \
    src/Entry/AppEntry.h \
    src/Entry/AppPlugin.h \
    src/Controller/ViewController.h \
    src/UI/NativeDefines.h

SOURCES += \
    src/Entry/AppEntry.cpp  \
    src/Entry/AppPlugin.cpp \
    src/Controller/ViewController.cpp \

INCLUDEPATH += \
    src/AppEntry \
    src/Controller \
    src/UI

RESOURCES += src/UI/View/view.qrc

OTHER_FILES += README.md
