/**
 * @file Definitions.h
 * @brief All definitions
 */

#ifndef EVO_DEFINITIONS_H
#define EVO_DEFINITIONS_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

// Global
#define EVO_NAME "evo"
#define EVO_INVALID_PID -1
#define EVO_INVALID_FD -1
#define EVO_MQ_LOOP "/loop_mq_evo"
#define EVO_GEOMETRY_X (0)
#define EVO_GEOMETRY_Y (0)
#define EVO_GEOMETRY_WIDTH (360)
#define EVO_GEOMETRY_HEIGHT (360)
#define EVO_RESOLUTION_X (0)
#define EVO_RESOLUTION_Y (0)
#define EVO_RESOLUTION_WIDTH (360)
#define EVO_RESOLUTION_HEIGHT (360)

// Log
#define LOG_NAME "Log"
#define LOG_LOG "Log"

// Wrapper
#define WRAPPER_NAME "Wrapper"
#define WRAPPER_LOG "Wrapper"

// Base
#define BASE_NAME "Base"
#define BASE_LOG "Base"

// AppServer
#define APPSERVER_NAME "AppServer"
#define APPSERVER_LOG "AppServer"
#define APPSERVER_APPMANAGER "AMS"

// AppManager
#define APPMANAGER_NAME "AppManager"
#define APPMANAGER_LOG "AppManager"
#define APPMANAGER_ENG_ZYGOTE "zygote_handle"
#define APPMANAGER_ENG_ZYGOTE_HELP "zygote_handle_help"
#define APPMANAGER_ENV_ZYGOTE_READ "zygote_read"
#define APPMANAGER_ENV_ZYGOTE_WRITE "zygote_write"
#define APPMANAGER_PATH_ZYGOTE "./EvoZygote"
#define APPMANAGER_NAME_ZYGOTE "EvoZygote"

// WindowManager
#define WINDOWMANAGER_NAME "WindowManager"
#define WINDOWMANAGER_LOG "WindowManager"
#define WINDOWMANAGER_PATH_SCREEN "qrc:///WindowManager/InitScreen.qml"

// AppController
#define APPCONTROLLER_NAME "AppController"
#define APPCONTROLLER_LOG "AppController"

// UI
#define UI_NAME "UI"
#define UI_LOG "UI"
#define UI_SCREENSHOT_NAME "evo_screenshot_default.png"

// Graphics
#define GRAPHICS_NAME "Graphics"
#define GRAPHICS_LOG "Graphics"

// Memfiler
#define MEMFILER_NAME "Memfiler"
#define MEMFILER_LOG "Memfiler"

// Zygote
#define ZYGOTE_NAME "Zygote"
#define ZYGOTE_LOG "Zygote"
#define ZYGOTE_ENV_HANDLE APPMANAGER_ENG_ZYGOTE
#define ZYGOTE_ENV_HANDLE_HELP APPMANAGER_ENG_ZYGOTE_HELP
#define ZYGOTE_ENV_READ APPMANAGER_ENV_ZYGOTE_READ
#define ZYGOTE_ENV_WRITE APPMANAGER_ENV_ZYGOTE_WRITE
#define ZYGOTE_PATH_APPLAUNCHER "./EvoAppLauncher"
#define ZYGOTE_NAME_APPLAUNCHER "EvoAppLauncher"
#define ZYGOTE_TYPE_APPLAUNCHER "Launcher"
#define ZYGOTE_PATH_AWS "./EvoAppWindowServer"
#define ZYGOTE_NAME_AWS "EvoAppWindowServer"
#define ZYGOTE_TYPE_AWS "WindowServer"
#define ZYGOTE_MSG_BUFSIZ 128
#define ZYGOTE_MSG_PARTS 4
#define ZYGOTE_MSG_SEP '/'
#define ZYGOTE_MSG_END '#'
#define ZYGOTE_MSG_FORK "zygote_fork" // format: zygote_fork/type/name#
#define ZYGOTE_MSG_ERROR "zygote_error" // format: zygote_error/pid/ppid#
#define ZYGOTE_MSG_EXIT "zygote_exit"
#define ZYGOTE_MSG_EXIT_LENGTH (11)

// AppLauncher
#define APPLAUNCHER_NAME "Applauncher"
#define APPLAUNCHER_LOG "Applauncher"
#define APPLANUCHER_MAINLOOP "mainloop"
#define APPLAUNCHER_SO "./../lib/libEvoAppLauncher.so"
#define APPLAUNCHER_MSG_EXIT "applauncher_exit"
#define APPLAUNCHER_MSG_EXIT_LENGTH (16)

// AppLauncherLib
#define APPLAUNCHERLIB_NAME "ApplauncherLib"
#define APPLAUNCHERLIB_LOG "ApplauncherLib"
#define APPLANUCHERLIB_PLUGIN "GetAppLauncherEntry"
#define APPLANUCHERLIB_SO "./../lib/libEvoAppLauncherPlugin.so"

// AppLauncherPlugin
#define APPLAUNCHERPLUGIN_NAME "QmlPlugin"
#define APPLAUNCHERPLUGIN_LOG "QmlPlugin"
#define APPLAUNCHERPLUGIN_APP "GetApplication"
#define APPLAUNCHERPLUGIN_SO_QMLDEMO "./../lib/libEvoApp_QmlDemo.so"

#endif // EVO_DEFINITIONS_H
