TARGET = TestLog
TEMPLATE = app

include($$PWD/../../EVO.pri)
DESTDIR = $$DESTDIR_BIN
LIBS += -lEvoLog

HEADERS += TestLog.h

SOURCES += TestLog.cpp

OTHER_FILES += README.md
