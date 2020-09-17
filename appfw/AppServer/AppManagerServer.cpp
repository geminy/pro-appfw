#include <mqueue.h>

#include "Definitions.h"
#include "log/Log.h"
#include "AppManagerServer.h"

EAppManagerServer::EAppManagerServer(INT32 argc, CHAR **argv)
    : EProcessable(APPSERVER_APPMANAGER, argc, argv)
    , m_zygoteQuit(FALSE)
    , m_launcherQuit(FALSE)
{
    evo_logd(APPSERVER_LOG, "EAppManagerServer::EAppManagerServer %s", m_name.c_str());
}

EAppManagerServer::~EAppManagerServer()
{
    evo_logd(APPSERVER_LOG, "EAppManagerServer::~EAppManagerServer");
}

VOID EAppManagerServer::initialize()
{
    evo_logd(APPSERVER_LOG, "EAppManagerServer::initialize begin");

    EProcessable::initialize();

    evo_logd(APPSERVER_LOG, "EAppManagerServer::initialize end");
}

VOID EAppManagerServer::start()
{
    evo_logd(APPSERVER_LOG, "EAppManagerServer::start");

    EProcessable::start();
}

INT32 EAppManagerServer::enterloop()
{
    evo_logd(APPSERVER_LOG, "EAppManagerServer::enterloop begin");

    loop();

    evo_logd(APPSERVER_LOG, "EAppManagerServer::enterloop end");

    return EProcessable::enterloop();
}

VOID EAppManagerServer::stop()
{
    evo_logd(APPSERVER_LOG, "EAppManagerServer::stop");

    EProcessable::stop();
}

VOID EAppManagerServer::finalize()
{
    evo_logd(APPSERVER_LOG, "EAppManagerServer::finalize begin");

    EProcessable::finalize();

    evo_logd(APPSERVER_LOG, "EAppManagerServer::finalize end");
}

VOID EAppManagerServer::quit(INT32 status)
{
    evo_logd(APPSERVER_LOG, "EAppManagerServer::quit begin status=%d", status);

    EProcessable::quit(status);
}

VOID EAppManagerServer::onInitialize()
{
    evo_logd(APPSERVER_LOG, "EAppManagerServer::onInitialize begin");
    evo_logd(APPSERVER_LOG, "EAppManagerServer::onInitialize end");
}

VOID EAppManagerServer::onStart()
{
    evo_logd(APPSERVER_LOG, "EAppManagerServer::onStart begin");
    evo_logd(APPSERVER_LOG, "EAppManagerServer::onStart end");
}

VOID EAppManagerServer::onStop()
{
    evo_logd(APPSERVER_LOG, "EAppManagerServer::onStop begin");
    evo_logd(APPSERVER_LOG, "EAppManagerServer::onStop end");
}

VOID EAppManagerServer::onFinalize()
{
    evo_logd(APPSERVER_LOG, "EAppManagerServer::onFinalize begin");
    evo_logd(APPSERVER_LOG, "EAppManagerServer::onFinalize end");
}

VOID EAppManagerServer::loop()
{
    evo_logd(APPSERVER_LOG, "#EAppManagerServer::loop begin");

    INT32 flags = O_CREAT /*| O_EXCL */| O_RDONLY;
    MODE_T modes = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    MQD_T mq = evo_mq_create(EVO_MQ_LOOP, flags, modes, NULL);
    ASSERT(-1 != mq);
    evo_logd(APPSERVER_LOG, "#EAppManagerServer::loop mq=%d", mq);

    mq_attr attr;
    evo_mq_getattr(mq, &attr);
    evo_logd(APPSERVER_LOG, "#EAppManagerServer::loop flags=%ld curmsgs=%ld maxmsg=%ld msgsize=%ld", attr.mq_flags, attr.mq_curmsgs, attr.mq_maxmsg, attr.mq_msgsize);

    CHAR *buf = (CHAR*)calloc(attr.mq_msgsize + 1, sizeof(CHAR));
    ASSERT(NULL != buf);

    while (TRUE) {
        evo_memset(buf, 0, attr.mq_msgsize);
        ASSERT(evo_mq_receive(mq, buf, attr.mq_msgsize, NULL) != -1);
        evo_logd(APPSERVER_LOG, "#EAppManagerServer::loop msg=%s", buf);

        if (evo_strncmp(buf, APPLAUNCHER_MSG_EXIT, APPLAUNCHER_MSG_EXIT_LENGTH) == 0) {
            m_launcherQuit = TRUE;
        }
        else if (evo_strncmp(buf, ZYGOTE_MSG_EXIT, ZYGOTE_MSG_EXIT_LENGTH) == 0) {
            m_zygoteQuit = TRUE;
        }

        if (m_launcherQuit && m_zygoteQuit) {
            break;
        }
    }

    evo_mq_close(mq);
    evo_mq_unlink(EVO_MQ_LOOP);

    evo_logd(APPSERVER_LOG, "#EAppManagerServer::loop end");
}
