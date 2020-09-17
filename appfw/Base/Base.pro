TARGET = EvoBase
TEMPLATE = lib

include($$PWD/../EVO.pri)
DESTDIR = $$DESTDIR_LIB
QMAKE_CXXFLAGS += -lpthread
QMAKE_LFLAGS += -lpthread
LIBS += -lEvoLog -lEvoWrapper

HEADERS += \
    include/base/AppConfig.h \
    include/base/AppContext.h \
    include/base/ISystem.h \
    include/base/ICreator.h \
    include/base/ILayer.h \
    include/base/IRootWindow.h \
    include/base/IMainWindow.h \
    include/base/IView.h \
    include/base/ISystemDelegate.h \
    include/base/CoreApplication.h \
    include/base/AppManager.h \
    include/base/CreatorManager.h \
    include/base/ViewManager.h \
    include/base/AppAPI.h

SOURCES += \
    System/CoreApplication.cpp \
    System/AppManager.cpp \
    System/CreatorManager.cpp \
    System/ViewManager.cpp \
    API/AppAPI.cpp

HEADERS += \
    include/base/Processable.h \
    include/base/Runnable.h \
    include/base/Thread.h \
    include/base/Mutex.h \
    include/base/Condition.h \
    include/base/RWLock.h \
    include/base/SpinLock.h \
    include/base/Barrier.h

SOURCES += \
    Thread/Thread.cpp \
    Thread/Mutex.cpp \
    Thread/Condition.cpp \
    Thread/RWLock.cpp \
    Thread/SpinLock.cpp \
    Thread/Barrier.cpp

OTHER_FILES += README.md
