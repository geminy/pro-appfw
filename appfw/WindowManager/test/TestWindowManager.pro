TARGET = TestWindowManager
TEMPLATE = app

include($$PWD/../../EVO.pri)
DESTDIR = $$DESTDIR_BIN
LIBS += -lEvoLog -lEvoWindowManager

HEADERS += TestWindowManager.h

SOURCES += TestWindowManager.cpp

OTHER_FILES += README.md
