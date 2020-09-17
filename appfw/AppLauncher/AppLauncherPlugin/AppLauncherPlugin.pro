TARGET = EvoAppLauncherPlugin
TEMPLATE = lib

include($$PWD/../../EVO.pri)
DESTDIR = $$DESTDIR_LIB
LIBS += -lEvoLog -lEvoWrapper -lEvoUI -lEvoWindowManager

HEADERS += QmlPlugin.h

SOURCES += QmlPlugin.cpp

OTHER_FILES += README.md
