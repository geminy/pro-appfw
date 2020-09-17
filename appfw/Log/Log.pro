TARGET = EvoLog
TEMPLATE = lib

include($$PWD/../EVO.pri)
DESTDIR = $$DESTDIR_LIB
QMAKE_CFLAGS += -lpthread
QMAKE_CXXFLAGS += -lpthread
QMAKE_LFLAGS += -lpthread
QMAKE_LFLAGS += -rdynamic

HEADERS += include/log/Log.h

SOURCES += Log.cpp

OTHER_FILES += README.md
