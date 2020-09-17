#include "log/Log.h"

#include <string>
#include <map>
#include <cstdio>
#include <cstdarg>
#include <cstring>
#include <cxxabi.h>
#include <pthread.h>

#define LogUtil_FilePath "./../../out/evo.log"
#define LogUtil_FileMode "a"

/**
 * @class __LogUtil
 * @brief Log utility
 *
 * m_fd:
 *          default: stdout
 *          file: LogUtil_FilePath
 *          external: registerLogFunc(LogFunction)
 *          priority: external > file > default
 */
class EVO_APICALL __LogUtil
{
public:
    __LogUtil()
        : m_fd(stdout)
        , m_toFile(FALSE)
        , m_func(NULL)
    {
        m_levelPair[Log_Debug] = LOG_DEBUG;
        m_levelPair[Log_Info] = LOG_INFO;
        m_levelPair[Log_Warn] = LOG_WARN;
        m_levelPair[Log_Error] = LOG_ERROR;
        m_levelPair[Log_Fatal] = LOG_FATAL;
        m_levelPair[Log_Location] = LOG_LOCATION;
        m_levelPair[Log_Function] = LOG_FUNCTION;
        m_levelPair[Log_Backtrace] = LOG_BACKTRACE;
    }

    ~__LogUtil()
    {
        m_func = NULL;
        if (m_toFile) {
            ASSERT2(fclose(m_fd) == 0);
        }
        m_fd = NULL;
    }

    BOOL logToFile(BOOL isFile)
    {
        if (NULL != m_func) {
            return FALSE;
        }

        if (isFile) {
            if (!m_toFile) {
                m_fd = fopen(LogUtil_FilePath, LogUtil_FileMode);
                ASSERT2(NULL != m_fd);
                m_toFile = TRUE;
            }
        }
        else {
            if (m_toFile) {
                ASSERT2(fclose(m_fd) == 0);
                m_fd = stdout;
                m_toFile = FALSE;
            }
        }

        return TRUE;
    }

    VOID registerLogFunc(LogFunction func)
    {
        m_func = func;
    }

    VOID log(LogLevel level, const CHAR *module, const CHAR *strings)
    {
        if (Log_Debug > level || Log_Backtrace < level) {
            return;
        }

        if (NULL != m_func) {
            m_func(level, module, strings);
            return;
        }

        m_buffer.clear();
        m_buffer.append(m_levelPair[level]);
        if (Log_Backtrace == level) {
            m_buffer.append(" [").append(strings).append("]");
            m_buffer.append(" [").append(module).append("]");
        }
        else {
            m_buffer.append(" [").append(module).append("]");
            m_buffer.append(" [").append(strings).append("]");
        }

        fprintf(m_fd, "%s\n", m_buffer.c_str());
        flush();
    }

    VOID flush()
    {
        fflush(m_fd);
    }

    static __LogUtil* Instance();

private:
    FILE  *m_fd;
    BOOL m_toFile;
    LogFunction m_func;
    std::map<LogLevel, std::string> m_levelPair;
    std::string m_buffer;

    static __LogUtil *m_self;
};

__LogUtil* __LogUtil::m_self = NULL;

__LogUtil* __LogUtil::Instance()
{
    if (NULL == m_self) {
        m_self = new __LogUtil;
    }
    return m_self;
}

/**************************************************/

#define LogUtilInst __LogUtil::Instance()
#define LogBufferSize 1024
static  pthread_mutex_t _LogMutex = PTHREAD_MUTEX_INITIALIZER;

BOOL LogToFile(BOOL isFile)
{
    ASSERT2(pthread_mutex_lock(&_LogMutex) == 0);

    BOOL ret = LogUtilInst->logToFile(isFile);

    ASSERT2(pthread_mutex_unlock(&_LogMutex) == 0);

    return ret;
}

VOID RegisterLogFunc(LogFunction func)
{
    ASSERT2(pthread_mutex_lock(&_LogMutex) == 0);

    LogUtilInst->registerLogFunc(func);

    ASSERT2(pthread_mutex_unlock(&_LogMutex) == 0);
}

VOID LogImpl(enum LogLevel level, const CHAR *module, const CHAR *format, ...)
{
    ASSERT2(pthread_mutex_lock(&_LogMutex) == 0);

    if (strlen(module) > 0) {
        CHAR strings[LogBufferSize] = { 0 };
        va_list args;
        va_start(args, format);
        INT32 size = vsnprintf(strings, LogBufferSize - 1, format, args);
        va_end(args);

        if (size > 0) {
            if (Log_Backtrace == level) {
#ifdef DEMANGLE
                CHAR *mangle = const_cast<CHAR*>(module);
                ASSERT2(NULL != mangle);
                const INT32 mangle_len_max = 128;
                SIZE_T mangle_len = strlen(mangle) + 1;
                CHAR demangle_buf[mangle_len_max] = { 0 };
                CHAR *function_name = (CHAR*)malloc(mangle_len);
                ASSERT2(NULL != function_name);
                CHAR *name_begin = 0;
                CHAR *offset_begin = 0;
                CHAR *offset_end = 0;
                for (CHAR *p = mangle; *p; ++p) {
                    if (strncmp("(",  p, 1) == 0) {
                        name_begin = p;
                    }
                    else if (name_begin && strncmp("+",  p, 1) == 0) {
                        offset_begin = p;
                    }
                    else if (offset_begin && strncmp(")",  p, 1) == 0) {
                        offset_end = p;
                        break;
                   }
                }
                if (offset_end) {
                    *name_begin++ = '\0';
                    *offset_begin++ = '\0';
                    *offset_end = '\0';
                    INT32 status = 1; // 0 -1 -2 -3
                    CHAR *demangled = abi::__cxa_demangle(name_begin, function_name, &mangle_len, &status);
                    if (0 == status) {
                        function_name = demangled;
                        sprintf(demangle_buf, "A%s:%s+%s", mangle, function_name, offset_begin);
                    }
                    else {
                        sprintf(demangle_buf, "B%s:%s()+%s", mangle, name_begin, offset_begin);
                    }
                }
                else {
                    sprintf(demangle_buf, "C%s", mangle);
                }
                free(function_name);

                LogUtilInst->log(level, demangle_buf, strings);
#else
                LogUtilInst->log(level, module, strings);
#endif
            }
            else {
                LogUtilInst->log(level, module, strings);
            }
        }
    }

    ASSERT2(pthread_mutex_unlock(&_LogMutex) == 0);
}
