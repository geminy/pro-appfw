TARGET = EvoWindowManager
TEMPLATE = lib
QT += qml quick gui core

include($$PWD/../EVO.pri)
DESTDIR = $$DESTDIR_LIB
LIBS += -lEvoLog

HEADERS += include/windowmanager/WindowManager.h

SOURCES += WindowManager.cpp

RESOURCES += screen/WindowScreen.qrc

OTHER_FILES += README.md

