/**
 * @file TestUI.h
 * @brief class TestUI
 */

#ifndef TESTUI_H
#define TESTUI_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "test/TestSuite.h"

/**
 * @class TestUI
 * @brief libEvoUI test
 */
class EVO_APICALL TestUI : public ETestSuite
{
public:
    TestUI();
    ~TestUI();

    VOID run();

private:
    VOID test_all();
};

#endif // TESTUI_H
