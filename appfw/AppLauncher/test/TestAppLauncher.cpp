#include "log/Log.h"
#include "TestAppLauncher.h"

#define TestAppLauncherTag "TestAppLauncher"

TestAppLauncher::TestAppLauncher()
    : ETestSuite(TestAppLauncherTag)
{
}

TestAppLauncher::~TestAppLauncher()
{
}

VOID TestAppLauncher::run()
{
    test_all();
}

VOID TestAppLauncher::test_all()
{
    evo_logd(TestAppLauncherTag, "TestAppLauncher::test_all");
}

EVO_TEST_RUN(TestAppLauncher)
