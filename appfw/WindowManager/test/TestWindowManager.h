/**
 * @file TestWindowManager.h
 * @brief class TestWindowManager
 */

#ifndef TESTWINDOWMANAGER_H
#define TESTWINDOWMANAGER_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "test/TestSuite.h"

/**
 * @class TestWindowManager
 * @brief libEvoWindowManager test
 */
class EVO_APICALL TestWindowManager : public ETestSuite
{
public:
    TestWindowManager();
    ~TestWindowManager();

    VOID run();

private:
    VOID test_all();
};

#endif // TESTWINDOWMANAGER_H
