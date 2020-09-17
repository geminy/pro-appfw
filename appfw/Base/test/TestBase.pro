TARGET = TestBase
TEMPLATE = app

include($$PWD/../../EVO.pri)
DESTDIR = $$DESTDIR_BIN
LIBS += -lEvoLog -lEvoWrapper -lEvoBase

HEADERS += TestBase.h

SOURCES += TestBase.cpp

OTHER_FILES += README.md
