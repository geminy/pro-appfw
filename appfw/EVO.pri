INCLUDEPATH += $$PWD/AppLauncher/AppLauncherLib/include
INCLUDEPATH += $$PWD/AppManager/include
INCLUDEPATH += $$PWD/Base/include
INCLUDEPATH += $$PWD/Global/include
INCLUDEPATH += $$PWD/Log/include
INCLUDEPATH += $$PWD/UI/include
INCLUDEPATH += $$PWD/WindowManager/include
INCLUDEPATH += $$PWD/Wrapper/include

DESTDIR_LIB = $$PWD/out/lib
DESTDIR_BIN = $$PWD/out/bin
OBJECTS_DIR = $$PWD/out/intermediates

LIBS += -L$$DESTDIR_LIB
QMAKE_RPATHDIR += $$DESTDIR_LIB
