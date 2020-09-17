#include <cstdio>

#include "log/Log.h"
#include "TestLog.h"

#define TestLogTag "TestLog"

static VOID _LogFunction(LogLevel level, const CHAR *module, const CHAR *strings)
{
    std::string buf("@");

    switch (level) {
    case Log_Debug:
        buf.append("debug");
        break;
    case Log_Info:
        buf.append("info");
        break;
    case Log_Warn:
        buf.append("warn");
        break;
    case Log_Error:
        buf.append("error");
        break;
    case Log_Fatal:
        buf.append("fatal");
        break;
    case Log_Location:
        buf.append("location");
        break;
    case Log_Function:
        buf.append("function");
        break;
    case Log_Backtrace:
        buf.append("backtrace");
        break;
    default:
        buf.append("?");
        break;
    }

    buf.append("@");
    buf.append(module);
    buf.append("@");
    buf.append(strings);
    buf.append("@");
    printf("%s\n", buf.c_str());
    fflush(stdout);
}

TestLog::TestLog()
    : ETestSuite(TestLogTag)
{
}

TestLog::~TestLog()
{
}

VOID TestLog::run()
{
    test_default();
    test_file();
    test_external();
    test_impl();
    test_macro();
}

VOID TestLog::test_default()
{
    evo_logd("", ""); // invalid
    evo_logd(TestLogTag, ""); // invalid
    evo_logd("", TestLogTag); // invalid
    evo_logd(TestLogTag, TestLogTag, TestLogTag); // third param is invalid
    evo_logd(TestLogTag, "TestLog::test_log debug");
    evo_logd(TestLogTag, "TestLog::test_log %s", "debug");

    evo_logi(TestLogTag, "TestLog::test_log info");
    evo_logi(TestLogTag, "TestLog::test_log %s", "info");

    evo_logw(TestLogTag, "TestLog::test_log warn");
    evo_logw(TestLogTag, "TestLog::test_log %s", "warn");

    evo_loge(TestLogTag, "TestLog::test_log error");
    evo_loge(TestLogTag, "TestLog::test_log %s", "error");

//    evo_logf(TestLogTag, "TestLog::test_log fatal"); // crash
//    evo_logf(TestLogTag, "TestLog::test_log %s", "fatal"); // crash

    evo_logl();
    evo_logfn();
    evo_logb();
}

VOID TestLog::test_file()
{
    LogToFile(TRUE);

    evo_logd(TestLogTag, "TestLog::test_file debug");
    evo_logi(TestLogTag, "TestLog::test_file info");
    evo_logw(TestLogTag, "TestLog::test_file warn");
    evo_loge(TestLogTag, "TestLog::test_file error");
    evo_logl();
    evo_logfn();
    evo_logb();

    LogToFile(FALSE);
}

VOID TestLog::test_external()
{
    RegisterLogFunc(_LogFunction);

    evo_logd(TestLogTag, "TestLog::test_external debug");
    evo_logi(TestLogTag, "TestLog::test_external info");
    evo_logw(TestLogTag, "TestLog::test_external warn");
    evo_loge(TestLogTag, "TestLog::test_external error");
    evo_logl();
    evo_logfn();
    evo_logb();

    RegisterLogFunc(NULL);
}

VOID TestLog::test_impl()
{
    LogImpl(Log_Debug, TestLogTag, "TestLog::test_impl");
    LogImpl(Log_Debug, TestLogTag, "%s", "TestLog::test_impl");
}

VOID TestLog::test_macro()
{
    BACKTRACE();
//    CRASH(); // crash
//    CRASH2(); // crash
//    ASSERT(0); // crash
    ASSERT(1);
//    ASSERT2(0); // crash
    ASSERT2(1);
//    ABORT(); // crash
}

EVO_TEST_RUN(TestLog)
