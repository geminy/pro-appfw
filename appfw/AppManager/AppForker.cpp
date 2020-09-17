#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>

#include "Definitions.h"
#include "log/Log.h"
#include "wrapper/Wrapper.h"
#include "base/Thread.h"
#include "base/Mutex.h"
#include "appmanager/AppForker.h"

static INT32 _Socket_parent_fd = EVO_INVALID_FD;
static INT32 _Socket_child_fd = EVO_INVALID_FD;
static BOOL _App_exit = FALSE;
static EMutex _App_state_mutex;

/**************************************************/

static VOID _SIGCHLD_handler(INT32 signum)
{
    evo_logd(APPMANAGER_LOG, "#_SIGCHLD_handler (sig=%d) begin", signum);

    PID_T pid;
    INT32 status;
    while (TRUE) {
        pid = evo_waitpid(-1, &status, WNOHANG);
        if (pid < 0) {
            evo_logd(APPMANAGER_LOG, "#_SIGCHLD_handler no child processes");
            break;
        }
        INT32 sig  = WTERMSIG(status);
        evo_logd(APPMANAGER_LOG, "#_SIGCHLD_handler sig=%d pid=%d", sig, pid);
    }

    evo_logd(APPMANAGER_LOG, "#_SIGCHLD_handler end");
}

// TODO message
static VOID _Send_message()
{
//    const CHAR *windowServer = "zygote_fork/WindowServer/EvoWindowServer#";
//    evo_write(_Socket_parent_fd, windowServer, evo_strlen(windowServer) + 1);

    const CHAR *launcher = "zygote_fork/Launcher/EvoAppLauncher#";
    evo_logd(APPMANAGER_LOG, "#_Send_message (write=%s) begin", launcher);
    evo_write(_Socket_parent_fd, launcher, evo_strlen(launcher) + 1);
    evo_logd(APPMANAGER_LOG, "#_Send_message end");
}

/**************************************************/

/**
 * @class __AppForkerMsgThread
 * @brief App forker message thread
 */
class EVO_APICALL __AppForkerMsgThread : public EThread
{
public:
    __AppForkerMsgThread()
    {
        evo_logd(APPMANAGER_LOG, "__AppForkerMsgThread::__AppForkerMsgThread");
    }

    ~__AppForkerMsgThread()
    {
        evo_logd(APPMANAGER_LOG, "__AppForkerMsgThread::~__AppForkerMsgThread");

        terminate();
    }

protected:
    VOID run()
    {
        evo_logd(APPMANAGER_LOG, "#__AppForkerMsgThread::run (pid=%d ppid=%d tid=%d ttid=%lu) begin", evo_getpid(), evo_getppid(), evo_gettid(), getTid());

        CHAR msgBf[ZYGOTE_MSG_BUFSIZ] = { 0 };
        INT32 msgSz = 0;
        fd_set readfds;
        FD_ZERO(&readfds);

        ASSERT(_Socket_parent_fd > 0);
        _Send_message();
        FD_SET(_Socket_parent_fd, &readfds);

        while (!_App_exit && _Socket_parent_fd > 0) {
            evo_select(_Socket_parent_fd + 1, &readfds, NULL, NULL, NULL);
            if (FD_ISSET(_Socket_parent_fd, &readfds)) {
                evo_memset(msgBf, 0, sizeof(msgBf));
                msgSz = evo_read(_Socket_parent_fd, msgBf, sizeof(msgBf) - 1);
                evo_logd(APPMANAGER_LOG,"#__AppForkerMsgThread::run fd=%d sz=%d msg=%s", _Socket_parent_fd, msgSz, msgBf);
            }
        }
        FD_CLR(_Socket_parent_fd, &readfds);

        evo_logd(APPMANAGER_LOG, "#__AppForkerMsgThread::run end");
    }
};

static __AppForkerMsgThread _AppForkerMsgThread;

/**************************************************/
/**
 * @class __AppZygote
 * @brief App zygote
 */
class EVO_APICALL __AppZygote
{
public:
    __AppZygote()
        : m_initialized(FALSE)
        , m_pid(EVO_INVALID_PID)
    {
        evo_logd(APPMANAGER_LOG, "__AppZygote::__AppZygote");
    }

    ~__AppZygote()
    {
        evo_logd(APPMANAGER_LOG, "__AppZygote::~__AppZygote");
    }

    VOID initialize()
    {
        evo_logd(APPMANAGER_LOG, "__AppZygote::initialize begin");

        if (m_initialized) {
            return;
        }

        INT32 sv_fd[2] = { 0 };
        if (evo_socketpair(AF_UNIX, SOCK_STREAM, 0, sv_fd) == -1) {
            ABORT();
        }
        _Socket_parent_fd = sv_fd[0];
        _Socket_child_fd = sv_fd[1];
        evo_logd(APPMANAGER_LOG, "#__AppZygote::initialize socketpair (%d, %d)", _Socket_parent_fd, _Socket_child_fd);

        PID_T fork_pid = evo_fork();
        if (0 == fork_pid) {
            evo_logd(APPMANAGER_LOG, "#__AppZygote::initialize child pid=%d ppid=%d", evo_getpid(), evo_getppid());

            evo_fcntl_int(_Socket_child_fd, F_SETFD, 0); // FD_CLOEXEC
            evo_fcntl_int(_Socket_parent_fd, F_SETFD, 0); // close-on-exec

            // TODO integer to string
            CHAR tmp[10 + 1] = { 0 };
            snprintf(tmp, 10, "%d", _Socket_child_fd);
            evo_setenv(APPMANAGER_ENG_ZYGOTE, tmp, 1);
            evo_memset(tmp, 0, sizeof(tmp));
            snprintf(tmp, 10, "%d", _Socket_parent_fd);
            evo_setenv(APPMANAGER_ENG_ZYGOTE_HELP, tmp, 1);

            if (evo_execl(APPMANAGER_PATH_ZYGOTE,
                          APPMANAGER_NAME_ZYGOTE,
                          EVOWRAPPER_PARAM_SENTINEL) == -1) {
                ABORT();
            }
        }
        else {
            m_pid = fork_pid;
            m_initialized = TRUE;
            evo_logd(APPMANAGER_LOG, "__AppZygote::initialize father pid=%d ppid=%d child=%d", evo_getpid(), evo_getppid(), m_pid);
            _AppForkerMsgThread.start();
        }

        evo_logd(APPMANAGER_LOG, "__AppZygote::initialize end");
    }

    VOID finalize()
    {
        evo_logd(APPMANAGER_LOG, "__AppZygote::finalize begin");

        EAutoMutex mutex(&_App_state_mutex);

        if (m_pid > 0) {
            evo_kill(m_pid, SIGKILL);
            m_pid = EVO_INVALID_PID;
        }

        // TODO sleep?
        evo_sleep(1);

        if (_Socket_parent_fd > 0) {
            evo_close(_Socket_parent_fd);
            _Socket_parent_fd = EVO_INVALID_FD;
        }

        if (_Socket_child_fd > 0) {
            evo_close(_Socket_child_fd);
            _Socket_child_fd = EVO_INVALID_FD;
        }

        _App_exit = TRUE;

        evo_logd(APPMANAGER_LOG, "__AppZygote::finalize end");
    }

private:
    BOOL m_initialized;
    PID_T m_pid;
};

static __AppZygote _AppZygote;

/**************************************************/

EAppFocker::EAppFocker()
{
    evo_logd(APPMANAGER_LOG, "EAppFocker::EAppFockek");
}

EAppFocker::~EAppFocker()
{
    evo_logd(APPMANAGER_LOG, "EAppFocker::~EAppFocker");
}

VOID EAppFocker::initialize()
{
    evo_logd(APPMANAGER_LOG, "EAppFocker::initialize begin");

    struct sigaction sa_child;
    sa_child.sa_handler = _SIGCHLD_handler;
    evo_memset(&sa_child.sa_mask, 0 , sizeof(sa_child.sa_mask));
    sa_child.sa_flags = 0;
    sa_child.sa_restorer = NULL;
    evo_sigaction(SIGCHLD, &sa_child, NULL);

    _AppZygote.initialize();

    evo_logd(APPMANAGER_LOG, "EAppFocker::initialize end");
}

VOID EAppFocker::finalize()
{
    evo_logd(APPMANAGER_LOG, "EAppFocker::finalize begin");

    _AppZygote.finalize();

    evo_logd(APPMANAGER_LOG, "EAppFocker::finalize end");
}
