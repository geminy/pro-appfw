TARGET = EvoAppManager
TEMPLATE = lib

include($$PWD/../EVO.pri)
DESTDIR = $$DESTDIR_LIB
LIBS += -lEvoLog -lEvoWrapper -lEvoBase

HEADERS += include/appmanager/AppForker.h

SOURCES += AppForker.cpp

OTHER_FILES += README.md
