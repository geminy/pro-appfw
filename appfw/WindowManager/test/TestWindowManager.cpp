#include "log/Log.h"
#include "windowmanager/WindowManager.h"
#include "TestWindowManager.h"

#define TestWindowManagerTag "TestWindowManager"

TestWindowManager::TestWindowManager()
    : ETestSuite(TestWindowManagerTag)
{
}

TestWindowManager::~TestWindowManager()
{
}

VOID TestWindowManager::run()
{
    test_all();   
}

VOID TestWindowManager::test_all()
{
    evo_logd(TestWindowManagerTag, "TestWindowManager::test_all");

    EWindowManager::Instance()->createApplication(0, NULL);
    EWindowManager::Instance()->createWindow();
    EWindowManager::Instance()->execApp();
    EWindowManager::Instance()->destroyWindow();
    EWindowManager::Instance()->destroyApplication();
}

EVO_TEST_RUN(TestWindowManager)
