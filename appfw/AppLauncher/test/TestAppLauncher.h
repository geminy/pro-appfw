/**
 * @file TestAppLauncher.h
 * @brief class TestAppLauncher
 */

#ifndef TESTAPPLAUNCHER_H
#define TESTAPPLAUNCHER_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "test/TestSuite.h"

/**
 * @class TestAppLauncher
 * @brief AppLauncher test
 */
class EVO_APICALL TestAppLauncher : public ETestSuite
{
public:
    TestAppLauncher();
    ~TestAppLauncher();

    VOID run();

private:
    VOID test_all();
};

#endif // TESTAPPLAUNCHER_H
