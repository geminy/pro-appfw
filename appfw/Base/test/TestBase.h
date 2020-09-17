/**
 * @file TestBase.h
 * @brief class TestBase
 */

#ifndef TESTBASE_H
#define TESTBASE_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "test/TestSuite.h"

/**
 * @class TestBase
 * @brief libEvoBase test
 */
class EVO_APICALL TestBase : public ETestSuite
{
public:
    TestBase();
    ~TestBase();

    VOID run();

private:
    VOID test_thread();
    VOID test_mutex();
    VOID test_cond();
    VOID test_rwlock();
    VOID test_spinlock();
    VOID test_barrier();
};

#endif // TESTBASE_H
