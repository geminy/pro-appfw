#include "Definitions.h"
#include "log/Log.h"
#include "wrapper/Wrapper.h"
#include "AppLauncherProc.h"

#include <mqueue.h>

static VOID _NotifyAppLauncherExit()
{
    evo_logd(APPLAUNCHER_LOG, "#_NotifyAppLauncherExit begin");

    INT32 flags = O_WRONLY;
    MQD_T mq = evo_mq_open(EVO_MQ_LOOP, flags);
    ASSERT(-1 != mq);
    evo_logd(APPLAUNCHER_LOG, "#_NotifyAppLauncherExit mq=%d", mq);

    ASSERT(evo_mq_send(mq, APPLAUNCHER_MSG_EXIT, APPLAUNCHER_MSG_EXIT_LENGTH + 1, 0) != -1);

    evo_mq_close(mq);

    evo_logd(APPLAUNCHER_LOG, "#_NotifyAppLauncherExit end");
}

int main(int argc, char **argv)
{
    evo_logd(APPLAUNCHER_LOG, "main (pid=%d ppid=%d) begin", evo_getpid(), evo_getppid());

    EAppLauncherProc launcher(argc, argv);
    launcher.prepare4App();
    launcher.prepare4AppWindow();
    launcher.entryApp();
    launcher.clean4AppWindow();
    launcher.clean4App();

    evo_logd(APPLAUNCHER_LOG, "main (pid=%d ppid=%d) end", evo_getpid(), evo_getppid());

    _NotifyAppLauncherExit();

    return 0;
}
