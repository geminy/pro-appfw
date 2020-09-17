/**
 * @file TestLog.h
 * @brief class TestLog
 */

#ifndef TESTLOG_H
#define TESTLOG_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "test/TestSuite.h"

/**
 * @class TestLog
 * @brief libEvoLog test
 */
class EVO_APICALL TestLog : public ETestSuite
{
public:
    TestLog();
    ~TestLog();

    VOID run();

private:
    VOID test_default();
    VOID test_file();
    VOID test_external();
    VOID test_impl();
    VOID test_macro();
};

#endif // TESTLOG_H
