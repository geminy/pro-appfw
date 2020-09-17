/**
 * @file TestWrapper.h
 * @brief class TestWrapper
 */

#ifndef TESTWRAPPER_H
#define TESTWRAPPER_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "test/TestSuite.h"

/**
 * @class TestWrapper
 * @brief libEvoWrapper test
 */
class EVO_APICALL TestWrapper : public ETestSuite
{
public:
    TestWrapper();
    ~TestWrapper();

    VOID run();

private:
    VOID test_env();
    VOID test_string();
    VOID test_string_number();
    VOID test_mem();
    VOID test_fd();
    VOID test_id();
    VOID test_process();
    VOID test_posix_mq();
    VOID test_pthread();
    VOID test_pthread_mutex();
    VOID test_pthread_condition();
    VOID test_pthread_rwlock();
    VOID test_pthread_spinlock();
    VOID test_pthread_barrier();
    VOID test_dl();
};

#endif // TESTWRAPPER_H
