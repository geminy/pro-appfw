/**
 * @file Log.h
 * @brief Log definitions
 */

#ifndef EVO_LOG_H
#define EVO_LOG_H

#include "Global.h"

#include <stdlib.h>
#include <assert.h>
#include <execinfo.h>

EVO_BEGIN_DECLS

/**
 * @enum LogLevel
 * @brief Log levels
 */
enum LogLevel
{
    Log_Debug,
    Log_Info,
    Log_Warn,
    Log_Error,
    Log_Fatal,

    Log_Location,
    Log_Function,
    Log_Backtrace
};

#define LOG_DEBUG "[debug]"
#define LOG_INFO "[info]"
#define LOG_WARN "[warn]"
#define LOG_ERROR "[error]"
#define LOG_FATAL "[fatal]"
#define LOG_LOCATION "[location]"
#define LOG_FUNCTION "[function]"
#define LOG_BACKTRACE "[backtrace]"

// c/cpp
typedef VOID(*LogFunction)(enum LogLevel level, const CHAR *module, const CHAR *strings);
EVO_APICALL BOOL LogToFile(BOOL isFile); // for extension, default to stdout
EVO_APICALL VOID RegisterLogFunc(LogFunction func); // for extension, a custom log implement
EVO_APICALL VOID LogImpl(enum LogLevel level, const CHAR *module, const CHAR *format, ...);

// debug mode
#define CONFIG_DEBUG 1
#if EVO_CONFIG(DEBUG)
# define evo_logd(tag, format, ...) LogImpl(Log_Debug, tag, format, ##__VA_ARGS__)
# define evo_logi(tag, format, ...) LogImpl(Log_Info, tag, format, ##__VA_ARGS__)
# define evo_logw(tag, format, ...) LogImpl(Log_Warn, tag, format, ##__VA_ARGS__)
# define evo_loge(tag, format, ...) LogImpl(Log_Error, tag, format, ##__VA_ARGS__)
# define evo_logf(tag, format, ...) \
    do { \
        LogImpl(Log_Fatal, tag, format, ##__VA_ARGS__); \
        BACKTRACE(); \
        CRASH(); \
    } while(0)
# define evo_logl() LogImpl(Log_Location, __FILE__, "%u", __LINE__)
# define evo_logfn() LogImpl(Log_Function, __PRETTY_FUNCTION__, "%s", "...")
# define evo_logb() \
    do { \
        LogImpl(Log_Location, __FILE__, "%u", __LINE__); \
        BACKTRACE(); \
    } while(0)
#else
# define evo_logd(tag, format, ...)
# define evo_logi(tag, format, ...)
# define evo_logw(tag, format, ...)
# define evo_loge(tag, format, ...)
# define evo_logf(tag, format, ...)
# define evo_logl()
# define evo_logfn()
# define evo_logb()
#endif

// symbols available with -rdynamic when linking
#define DEMANGLE
#define BACKTRACE_SIZE 32
#define BACKTRACE() \
    do { \
        VOID *buf[BACKTRACE_SIZE] = { 0 }; \
        INT32 size = backtrace(buf, BACKTRACE_SIZE); \
        CHAR **traces = backtrace_symbols(buf, size); \
        if (NULL != traces) { \
            INT32 i = 0; \
            for (; i < size; ++i) {\
                LogImpl(Log_Backtrace, traces[i], "%u", i); \
            } \
            free(traces); \
        } \
    } while (0)

#define CRASH() (*(UINT32*)0X0 = 0XABCDEFFF)
#define CRASH2() (((VOID(*)())0X0)())
#define ASSERT(cond) \
    if (!(cond)) { \
        LogImpl(Log_Fatal, "AssertFailed", "%s %u", __FILE__, __LINE__); \
        CRASH(); \
    }
#define ASSERT2 assert
#define ABORT abort

EVO_END_DECLS

#endif // EVO_LOG_H
