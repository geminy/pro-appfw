#include "Definitions.h"
#include "log/Log.h"
#include "wrapper/Wrapper.h"

#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <mqueue.h>

static INT32 _ZygoteFd = EVO_INVALID_PID;
static INT32 _ZygoteFdHelp = EVO_INVALID_PID;

static VOID _ChildHandler(INT32 signum)
{
    evo_logd(ZYGOTE_LOG, "#_ChildHandler (sig=%d) begin", signum);

    PID_T pid;
    INT32 status;
    while (TRUE) {
        pid = evo_waitpid(-1, &status, WNOHANG);
        if (pid < 0) {
            evo_logd(ZYGOTE_LOG, "#_ChildHandler no child processes");
            break;
        }
        INT32 sig  = WTERMSIG(status);
        evo_logd(ZYGOTE_LOG, "#_ChildHandler sig=%d pid=%d", sig, pid);
    }

    evo_logd(ZYGOTE_LOG, "#_ChildHandler end");
}

static VOID _SetChildHandle()
{
    struct sigaction sa_child;
    sa_child.sa_handler = _ChildHandler;
    evo_memset(&sa_child.sa_mask, 0 , sizeof(sa_child.sa_mask));
    sa_child.sa_flags = 0;
    sa_child.sa_restorer = NULL;
    evo_sigaction(SIGCHLD, &sa_child, NULL);
}

static VOID _SigpipeHandler(INT32 signum)
{
    evo_logf(ZYGOTE_LOG, "#_SigpipeHandler sig=%d pid=%d", signum, evo_getpid());
}

static VOID _SetSigpipeHandle()
{
    struct sigaction sa_pipe;
    sa_pipe.sa_handler = _SigpipeHandler;
    evo_memset(&sa_pipe.sa_mask, 0 , sizeof(sa_pipe.sa_mask));
    sa_pipe.sa_flags = 0;
    sa_pipe.sa_restorer = NULL;
    evo_sigaction(SIGPIPE, &sa_pipe, NULL);
}

static BOOL _ParseMsg(const CHAR *buf, CHAR *first, CHAR *second, CHAR *third)
{
    BOOL ret = FALSE;
    INT32 pos[ZYGOTE_MSG_PARTS] = { 0 };
    INT32 count = 1;

    for (INT32 index = 0; index < ZYGOTE_MSG_BUFSIZ && count < ZYGOTE_MSG_PARTS; ++index) {
        if (ZYGOTE_MSG_SEP == buf[index] || ZYGOTE_MSG_END == buf[index]) {
            pos[count++] = index;
        }
        else if ('\0' == buf[index]) {
            break;
        }
    }

    if (ZYGOTE_MSG_PARTS == count) {
        memcpy(first, buf, pos[1] - pos[0]);
        memcpy(second, buf + pos[1] + 1, pos[2] - pos[1] - 1);
        memcpy(third, buf + pos[2] + 1, pos[3] - pos[2] - 1);
        ret = TRUE;
    }

    if (!ret) {
        evo_logd(ZYGOTE_LOG, "#_ParseMsg %s error", buf);
    }

    return ret;
}

static VOID _NotifyZygoteExit()
{
    evo_logd(ZYGOTE_LOG, "#_NotifyZygoteExit begin");

    INT32 flags = O_WRONLY;
    MQD_T mq = evo_mq_open(EVO_MQ_LOOP, flags);
    ASSERT(-1 != mq);
    evo_logd(ZYGOTE_LOG, "#_NotifyZygoteExit mq=%d", mq);

    ASSERT(evo_mq_send(mq, ZYGOTE_MSG_EXIT, ZYGOTE_MSG_EXIT_LENGTH + 1, 0) != -1);

    evo_mq_close(mq);

    evo_logd(ZYGOTE_LOG, "#_NotifyZygoteExit end");
}

int main(int argc, char **argv)
{
    EVO_UNUSED(argc);
    EVO_UNUSED(argv);

    evo_logd(ZYGOTE_LOG, "main (pid=%d ppid=%d) begin", evo_getpid(), evo_getppid());

    CHAR *env = evo_getenv(ZYGOTE_ENV_HANDLE);
    ASSERT(NULL != env);
    _ZygoteFd = evo_atoi(env);
    env = evo_getenv(ZYGOTE_ENV_HANDLE_HELP);
    ASSERT(NULL != env);
    _ZygoteFdHelp = evo_atoi(env);
    evo_logd(ZYGOTE_LOG, "main %s=%d %s=%d", ZYGOTE_ENV_HANDLE, _ZygoteFd, ZYGOTE_ENV_HANDLE_HELP, _ZygoteFdHelp);

    PID_T ppid = evo_getppid();
    //TODO EPERM
    evo_logd(ZYGOTE_LOG, "main pgid=%d", evo_getpgid(0));
    evo_setpgid(0, ppid);
    evo_logd(ZYGOTE_LOG, "main pgid=%d", evo_getpgid(0));

    _SetChildHandle();
    _SetSigpipeHandle();

    CHAR msg[ZYGOTE_MSG_BUFSIZ] = { 0 };

    while (TRUE) {
        evo_memset(msg, 0, sizeof(msg));
        INT32 size = evo_read(_ZygoteFd, msg, sizeof(msg) - 1);
        if (-1 == size) {
            evo_logd(ZYGOTE_LOG, "#main read %d error", _ZygoteFd);
        }
        else if (0 == size) {
            evo_logd(ZYGOTE_LOG, "#main read %d null", _ZygoteFd);
        }
        else if (evo_getppid() == ppid) {
            evo_logd(ZYGOTE_LOG, "#main read %d %s", _ZygoteFd, msg);

            CHAR msg_first[ZYGOTE_MSG_BUFSIZ] = { 0 };
            CHAR msg_second[ZYGOTE_MSG_BUFSIZ] = { 0 };
            CHAR msg_third[ZYGOTE_MSG_BUFSIZ] = { 0 };
            if (_ParseMsg(msg, msg_first, msg_second, msg_third)) {
                evo_logd(ZYGOTE_LOG, "#main message %s/%s/%s#", msg_first, msg_second, msg_third);
            }

            // fork
            if (evo_strcmp(msg_first, ZYGOTE_MSG_FORK) == 0) {
                // AppLauncher
                if (evo_strcmp(msg_second, ZYGOTE_TYPE_APPLAUNCHER) == 0) {
                    PID_T pid = fork();
                    if (0 == pid) {
                        evo_logd(ZYGOTE_LOG, "#main fork %s", ZYGOTE_NAME_APPLAUNCHER);

                        evo_execl(ZYGOTE_PATH_APPLAUNCHER,
                                  ZYGOTE_NAME_APPLAUNCHER,
                                  EVOWRAPPER_PARAM_SENTINEL);
                    }
                    break;
                }
                // TODO add AppWindowServer
                else if (evo_strcmp(msg_second, ZYGOTE_TYPE_AWS) == 0) {
                    PID_T pid = fork();
                    if (0 == pid) {
                        evo_logd(ZYGOTE_LOG, "#main fork %s", ZYGOTE_NAME_AWS);

                        evo_execl(ZYGOTE_PATH_AWS,
                                  ZYGOTE_NAME_AWS,
                                  EVOWRAPPER_PARAM_SENTINEL);
                    }
                    break;
                }
            }
            // others
            else {
            }
        }
        else {
            evo_logd(ZYGOTE_LOG, "#main error pid=%d oppid=%d nppid=%d pgid=%d",
                 evo_getpid(), ppid, evo_getppid(), evo_getpgid(0));

            CHAR msg[ZYGOTE_MSG_BUFSIZ] = { 0 };
            snprintf(msg, ZYGOTE_MSG_BUFSIZ - 1, "%s/%d/%d#",
                     ZYGOTE_MSG_ERROR, evo_getpid(), evo_getppid());
            evo_write(_ZygoteFd, msg, evo_strlen(msg) + 1);
            evo_logd(APPMANAGER_LOG, "#main write %d %s", _ZygoteFd, msg);
        }
    }

    evo_close(_ZygoteFd);
    _ZygoteFd = EVO_INVALID_FD;
    evo_close(_ZygoteFdHelp);
    _ZygoteFdHelp = EVO_INVALID_FD;

    evo_waitpid(-1, NULL, 0);
    _NotifyZygoteExit();

    evo_logd(ZYGOTE_LOG, "main (pid=%d ppid=%d) end", evo_getpid(), evo_getppid());

    return 0;
}
