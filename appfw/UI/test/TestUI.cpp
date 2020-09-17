#include "log/Log.h"
#include "TestUI.h"

#define TestUITag "TestUI"

TestUI::TestUI()
    : ETestSuite(TestUITag)
{
}

TestUI::~TestUI()
{
}

VOID TestUI::run()
{
    test_all();   
}

VOID TestUI::test_all()
{
    evo_logd(TestUITag, "TestUI::test_all");
}

EVO_TEST_RUN(TestUI)
