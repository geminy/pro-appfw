TARGET = TestAppLauncher
TEMPLATE = app

include($$PWD/../../EVO.pri)
DESTDIR = $$DESTDIR_BIN
LIBS += -lEvoLog

HEADERS += TestAppLauncher.h

SOURCES += TestAppLauncher.cpp

OTHER_FILES += README.md
