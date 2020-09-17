TARGET = EvoAppLauncher
TEMPLATE = app

include($$PWD/../../EVO.pri)
DESTDIR = $$DESTDIR_BIN
LIBS += -lEvoLog -lEvoWrapper -lEvoWindowManager
LIBS += -ldl

HEADERS += AppLauncherProc.h

SOURCES += \
    AppLauncherMain.cpp \
    AppLauncherProc.cpp

OTHER_FILES += README.md
