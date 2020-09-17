TARGET = TestWrapper
TEMPLATE = app

include($$PWD/../../EVO.pri)
DESTDIR = $$DESTDIR_BIN
LIBS += -lEvoLog -lEvoWrapper

HEADERS += TestWrapper.h

SOURCES += TestWrapper.cpp

OTHER_FILES += README.md
