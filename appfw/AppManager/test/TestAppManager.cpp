#include "log/Log.h"
#include "appmanager/AppForker.h"
#include "TestAppManager.h"

#define TestAppManagerTag "TestAppManager"

TestAppManager::TestAppManager()
    : ETestSuite(TestAppManagerTag)
{
}

TestAppManager::~TestAppManager()
{
}

VOID TestAppManager::run()
{
    test_all();
}

VOID TestAppManager::test_all()
{
    evo_logd(TestAppManagerTag, "TestAppManager::test_all");

    EAppFocker af;
    af.initialize();
    af.finalize();
}

EVO_TEST_RUN(TestAppManager)
