/**
 * @file AppManagerServer.h
 * @brief class EAppManagerServer
 */

#ifndef EVO_APPMANAGERSERVER_H
#define EVO_APPMANAGERSERVER_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"
#include "base/Processable.h"

/**
 * @class EAppManagerServer
 * @brief App manager server
 */
class EVO_APICALL EAppManagerServer : public EProcessable
{
public:
    EAppManagerServer(INT32 argc, CHAR **argv);
    ~EAppManagerServer();

    VOID initialize();
    VOID start();
    INT32 enterloop();
    VOID stop();
    VOID finalize();
    VOID quit(INT32 status);

protected:
    VOID onInitialize();
    VOID onStart();
    VOID onStop();
    VOID onFinalize();

private:
    VOID loop();

    EVO_DISABLE_COPY(EAppManagerServer)

    BOOL m_zygoteQuit;
    BOOL m_launcherQuit;
};

#endif // EVO_APPMANAGERSERVER_H
