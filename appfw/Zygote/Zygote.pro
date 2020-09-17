TARGET = EvoZygote
TEMPLATE = app

include($$PWD/../EVO.pri)
DESTDIR = $$DESTDIR_BIN
LIBS += -lEvoLog -lEvoWrapper

SOURCES += ZygoteMain.cpp

OTHER_FILES += README.md
