TARGET = TestAppManager
TEMPLATE = app

include($$PWD/../../EVO.pri)
DESTDIR = $$DESTDIR_BIN
LIBS += -lEvoLog -lEvoAppManager

HEADERS += TestAppManager.h

SOURCES += TestAppManager.cpp

OTHER_FILES += README.md
