TARGET = TestUI
TEMPLATE = app

include($$PWD/../../EVO.pri)
DESTDIR = $$DESTDIR_BIN
LIBS += -lEvoLog -lEvoUI

HEADERS += TestUI.h

SOURCES += TestUI.cpp

OTHER_FILES += README.md
