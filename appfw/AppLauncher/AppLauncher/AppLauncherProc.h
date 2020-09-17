/**
 * @file AppLauncherProc.h
 * @brief class EAppLauncherProc
 */

#ifndef EVO_APPLAUNCHERPROC_H
#define EVO_APPLAUNCHERPROC_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"
#include "base/Processable.h"

/**
 * @class EAppLauncherProc
 * @brief App launcher process
 */
class EVO_APICALL EAppLauncherProc : public EProcessable
{
public:
    EAppLauncherProc(INT32 argc, CHAR **argv);
    ~EAppLauncherProc();

    VOID prepare4App();
    VOID prepare4AppWindow();
    VOID entryApp(INT32 flag = -1);
    VOID clean4AppWindow();
    VOID clean4App();

protected:
    VOID onInitialize();
    VOID onStart();
    VOID onStop();
    VOID onFinalize();

private:
    EVO_DISABLE_COPY(EAppLauncherProc)

    INT32 m_argc;
    CHAR **m_argv;
};

#endif // EVO_APPLAUNCHERPROC_H
