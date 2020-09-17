TARGET = EvoAppServer
TEMPLATE = app

include($$PWD/../EVO.pri)
DESTDIR = $$DESTDIR_BIN
LIBS += -lEvoLog -lEvoWrapper -lEvoAppManager

HEADERS += AppManagerServer.h

SOURCES += \
    AppServerMain.cpp \
    AppManagerServer.cpp

OTHER_FILES += README.md
