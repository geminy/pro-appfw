TARGET = EvoUI
TEMPLATE = lib
QT += qml quick gui core

include($$PWD/../EVO.pri)
DESTDIR = $$DESTDIR_LIB
LIBS += -lEvoLog -lEvoWindowManager -lEvoBase

HEADERS += \
    include/ui/API.h \
    include/ui/Layer.h \
    include/ui/RootWindow.h \
    include/ui/MainWindow.h \
    include/ui/Item.h \
    include/ui/View.h \
    include/ui/ViewCreator.h \
    include/ui/Application.h \
    include/ui/SystemDelegate.h \
    include/ui/FileLoader.h

SOURCES += \
    API/API.cpp \
    Window/Layer.cpp \
    Window/RootWindow.cpp \
    Window/MainWindow.cpp \
    Window/Item.cpp \
    Window/View.cpp \
    Window/ViewCreator.cpp \
    System/Application.cpp \
    System/SystemDelegate.cpp \
    Resource/FileLoader.cpp

OTHER_FILES += README.md
