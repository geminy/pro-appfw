TARGET = EvoWrapper
TEMPLATE = lib

include($$PWD/../EVO.pri)
DESTDIR = $$DESTDIR_LIB
DEFINES += _GNU_SOURCE
QMAKE_CFLAGS += -lpthread
QMAKE_CXXFLAGS += -lpthread
QMAKE_LFLAGS += -lpthread
LIBS += -lEvoLog
LIBS += -ldl -lrt

HEADERS += include/wrapper/Wrapper.h

SOURCES += Wrapper.c

OTHER_FILES += README.md
