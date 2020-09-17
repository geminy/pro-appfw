TARGET = EvoAppLauncher
TEMPLATE = lib

include($$PWD/../../EVO.pri)
DESTDIR = $$DESTDIR_LIB
LIBS += -lEvoLog -lEvoWrapper

HEADERS += \
    include/applauncher/IApp.h \
    include/applauncher/AppLauncherBase.h \
    AppLauncher.h \
    AppLauncherManager.h \
    AppContext.h \
    AppContextManager.h \
    AppPluginManager.h \
    AppFrameworkCallback.h

SOURCES += \
    AppLauncher.cpp \
    AppLauncherManager.cpp \
    AppContext.cpp \
    AppContextManager.cpp \
    AppPluginManager.cpp \
    AppFrameworkCallback.cpp

OTHER_FILES += README.md
