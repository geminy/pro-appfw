/**
 * @file TestSuite.h
 * @brief class ETestSuite
 */

#ifndef EVO_TESTSUITE_H
#define EVO_TESTSUITE_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"

#include <iostream>
#include <string>

/**
 * @class ETestSuite
 * @brief Test suite
 */
class EVO_APICALL ETestSuite
{
public:
    explicit ETestSuite(const std::string &module) : m_module(module) {}
    virtual ~ETestSuite() {}
    virtual VOID run() = 0;

    VOID begin()
    {
        std::cout << "********** ";
        std::cout << m_module;
        std::cout << " BEGIN";
        std::cout << " **********";
        std::cout << std::endl;
    }

    VOID end()
    {
        std::cout << "********** ";
        std::cout << m_module;
        std::cout << " END";
        std::cout << " **********";
        std::cout << std::endl;
    }

private:
    EVO_DISABLE_COPY(ETestSuite)

    std::string m_module;
};

// Class: derived from class ETestSuite
#define EVO_TEST_RUN(Class) \
    int main(int argc, char **argv) \
    { \
        EVO_UNUSED(argc); \
        EVO_UNUSED(argv); \
        std::cout << "********** EVO TEST BEGIN **********" << std::endl; \
        std::cout << std::endl; \
        Class _test; \
        _test.begin(); \
        _test.run(); \
        _test.end(); \
        std::cout << std::endl; \
        std::cout << "********** EVO TEST END **********" << std::endl; \
        return 0; \
    }

#endif // EVO_TESTSUITE_H
