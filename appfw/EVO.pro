##################################################
# Project: EVO - Lightweight App Framework                                              #
##################################################

TEMPLATE = subdirs

##################################################

# Evo-Log
SUBDIRS += Log
Log.file = Log/Log.pro
Log.depends +=

# Evo-TestLog
SUBDIRS += TestLog
TestLog.file = Log/test/TestLog.pro
TestLog.depends += Log

##################################################

# Evo-Wrapper
SUBDIRS += Wrapper
Wrapper.file = Wrapper/Wrapper.pro
Wrapper.depends += Log

# Evo-TestWrapper
SUBDIRS += TestWrapper
TestWrapper.file = Wrapper/test/TestWrapper.pro
TestWrapper.depends += Wrapper

##################################################

# Evo-Base
SUBDIRS += Base
Base.file = Base/Base.pro
Base.depends += Wrapper

# Evo-TestBase
SUBDIRS += TestBase
TestBase.file = Base/test/TestBase.pro
TestBase.depends += Base

##################################################

# Evo-AppManager
SUBDIRS += AppManager
AppManager.file = AppManager/AppManager.pro
AppManager.depends += Base Zygote

# Evo-TestAppManager
SUBDIRS += TestAppManager
TestAppManager.file = AppManager/test/TestAppManager.pro
TestAppManager.depends += AppManager

##################################################

# Evo-WindowManager
SUBDIRS += WindowManager
WindowManager.file = WindowManager/WindowManager.pro
WindowManager.depends += Log

# Evo-TestWindowManager
SUBDIRS += TestWindowManager
TestWindowManager.file = WindowManager/test/TestWindowManager.pro
TestWindowManager.depends += WindowManager

##################################################

# Evo-UI
SUBDIRS += UI
UI.file = UI/UI.pro
UI.depends += Log WindowManager Base

# Evo-TestUI
SUBDIRS += TestUI
TestUI.file = UI/test/TestUI.pro
TestUI.depends += UI

##################################################

# Evo-AppServer
SUBDIRS += AppServer
AppServer.file = AppServer/AppServer.pro
AppServer.depends += AppManager

##################################################

# Evo-Zygote
SUBDIRS += Zygote
Zygote.file = Zygote/Zygote.pro
Zygote.depends += Wrapper

##################################################

# Evo-AppLauncher
SUBDIRS += AppLauncher
AppLauncher.file = AppLauncher/AppLauncher/AppLauncher.pro
AppLauncher.depends += AppLauncherLib WindowManager

# Evo-AppLauncherLib
SUBDIRS += AppLauncherLib
AppLauncherLib.file = AppLauncher/AppLauncherLib/AppLauncherLib.pro
AppLauncherLib.depends += AppLauncherPlugin

# Evo-AppLauncherPlugin
SUBDIRS += AppLauncherPlugin
AppLauncherPlugin.file = AppLauncher/AppLauncherPlugin/AppLauncherPlugin.pro
AppLauncherPlugin.depends += Wrapper WindowManager UI QmlDemo

# Evo-TestAppLauncher
SUBDIRS += TestAppLauncher
TestAppLauncher.file = AppLauncher/test/TestAppLauncher.pro
TestAppLauncher.depends += AppLauncher

##################################################

# Evo-QmlDemo
SUBDIRS += QmlDemo
QmlDemo.file = Apps/QmlDemo/QmlDemo.pro
QmlDemo.depends += Log UI

##################################################

include(EVO.pri)

##################################################

HEADERS += \
    Global/include/Global.h \
    Global/include/Definitions.h \
    Global/include/test/TestSuite.h

##################################################

OTHER_FILES += \
    README \
    foremost.sh
