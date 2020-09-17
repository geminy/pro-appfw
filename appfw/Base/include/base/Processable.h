/**
 * @file Processable.h
 * @brief class EProcessable
 */

#ifndef EVO_PROCESSABLE_H
#define EVO_PROCESSABLE_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include <string>
#include <unistd.h>

#include "Global.h"
#include "wrapper/Wrapper.h"

/**
 * @class EProcessable
 * @brief Abstract class
 */
class EVO_APICALL EProcessable
{
public:
    EProcessable(INT32 argc, CHAR **argv)
        : m_name(argv[0])
    {
        EVO_UNUSED(argc);
    }

    EProcessable(const CHAR *name, INT32 argc, CHAR **argv)
        : m_name(name)
    {
        EVO_UNUSED(argc);
        EVO_UNUSED(argv);
    }

    virtual ~EProcessable() {}

    virtual VOID initialize()
    {
        onInitialize();
    }

    virtual VOID start()
    {
        onStart();
    }

    // TODO enterloop
    virtual INT32 enterloop()
    {
        return 0;
    }

    virtual VOID stop()
    {
        onStop();
    }

    virtual VOID finalize()
    {
        onFinalize();
    }

    virtual VOID quit(INT32 status)
    {
        evo_kill(evo_getpid(), status);
    }

protected:
    virtual VOID onInitialize() = 0;
    virtual VOID onStart() = 0;
    virtual VOID onStop() = 0;
    virtual VOID onFinalize() = 0;

    std::string m_name;

private:
    EVO_DISABLE_COPY(EProcessable)
};

#endif // EVO_PROCESSABLE_H
