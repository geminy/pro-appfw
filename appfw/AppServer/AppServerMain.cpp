#include "Definitions.h"
#include "log/Log.h"
#include "wrapper/Wrapper.h"
#include "appmanager/AppForker.h"
#include "AppManagerServer.h"

int main(int argc, char **argv)
{
    evo_logd(APPSERVER_LOG, "main (pid=%d ppid=%d) begin", evo_getpid(), evo_getppid());

    EAppFocker af;
    af.initialize();

    EAppManagerServer ams(argc, argv);
    ams.initialize();
    ams.start();
    ams.enterloop();
    ams.stop();
    ams.finalize();

    af.finalize();

    evo_logd(APPSERVER_LOG, "main (pid=%d ppid=%d) end", evo_getpid(), evo_getppid());

    return 0;
}
