/**
 * @file TestAppManager.h
 * @brief class TestAppManager
 */

#ifndef TESTAPPMANAGER_H
#define TESTAPPMANAGER_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "test/TestSuite.h"

/**
 * @class TestAppManager
 * @brief libEvoAppManager test
 */
class EVO_APICALL TestAppManager : public ETestSuite
{
public:
    TestAppManager();
    ~TestAppManager();

    VOID run();

private:
    VOID test_all();
};

#endif // TESTAPPMANAGER_H
