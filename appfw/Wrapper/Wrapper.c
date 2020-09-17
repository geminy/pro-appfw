#include "log/Log.h"
#include "wrapper/Wrapper.h"

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <dlfcn.h>
#include <sys/auxv.h>
#include <mqueue.h>

#include <sys/socket.h>
#include <sys/wait.h>

CHAR* evo_getenv(const CHAR *name)
{
    return getenv(name);
}

CHAR* evo_secure_getenv(const CHAR *name)
{
#ifdef _GNU_SOURCE
    return secure_getenv(name);
#endif

    EVO_UNUSED(name);
    evo_loge(EVOWRAPPER_SECURE_GETENV, "macro %s is needed", "_GNU_SOURCE");
    return NULL;
}

INT32 evo_putenv(CHAR *string)
{
    errno = 0;
    INT32 ret = putenv(string);
    if (0 != ret) {
        const INT32 _errno = errno;
        evo_loge(EVOWRAPPER_PUTENV, "%s", strerror(_errno));
    }
    return ret;
}

INT32 evo_setenv(const CHAR *name, const CHAR *value, INT32 overwrite)
{
    errno = 0;
    INT32 ret = setenv(name, value, overwrite);
    if (-1 == ret) {
        const INT32 _errno = errno;
        evo_loge(EVOWRAPPER_SETENV, "%s", strerror(_errno));
    }
    return ret;
    secure_getenv("");
}

INT32 evo_unsetenv(const CHAR *string)
{
    errno = 0;
    INT32 ret = unsetenv(string);
    if (-1 == ret) {
        const INT32 _errno = errno;
        evo_loge(EVOWRAPPER_UNSETENV, "%s", strerror(_errno));
    }
    return ret;
}

INT32 evo_clearenv()
{
    INT32 ret = clearenv();
    if (0 != ret) {
        evo_loge(EVOWRAPPER_CLEARENV, "clearenv");
    }
    return ret;
}

ULONG evo_getauxval(ULONG type)
{
    ULONG ret = getauxval(type);
    if (0 == ret) {
        evo_loge(EVOWRAPPER_GETAUXVAL, "type(%lu) is not found", type);
    }
    return ret;
}

/**************************************************/

CHAR* evo_stpcpy(CHAR *dest, const CHAR *src)
{
    return stpcpy(dest, src);
}

CHAR* evo_strcat(CHAR *dest, const CHAR *src)
{
    return strcat(dest, src);
}

CHAR* evo_strncat(CHAR *dest, const CHAR *src, SIZE_T n)
{
    return strncat(dest, src, n);
}

CHAR* evo_strchr(const CHAR *s, INT32 c)
{
    return strchr(s, c);
}

CHAR* evo_strrchr(const CHAR *s, INT32 c)
{
    return strrchr(s, c);
}

CHAR* evo_strchrnul(const CHAR *s, INT32 c)
{
#ifdef _GNU_SOURCE
    return strchrnul(s, c);
#endif

    EVO_UNUSED(s);
    EVO_UNUSED(c);
    evo_loge(EVOWRAPPER_STRCHRNUL, "macro %s is needed", "_GNU_SOURCE");
    return NULL;
}

INT32 evo_strcmp(const CHAR *s1, const CHAR *s2)
{
    return strcmp(s1, s2);
}

INT32 evo_strncmp(const CHAR *s1, const CHAR *s2, SIZE_T n)
{
    return strncmp(s1, s2, n);
}

INT32 evo_strcoll(const CHAR *s1, const CHAR *s2)
{
    return strcoll(s1, s2);
}

CHAR* evo_strcpy(CHAR *dest, const CHAR *src)
{
    return strcpy(dest, src);
}

CHAR* evo_strncpy(CHAR *dest, const CHAR *src, SIZE_T n)
{
    return strncpy(dest, src, n);
}

SIZE_T evo_strspn(const CHAR *s, const CHAR *accept)
{
    return strspn(s, accept);
}

SIZE_T evo_strcspn(const CHAR *s, const CHAR *reject)
{
    return strcspn(s, reject);
}

CHAR* evo_strdup(const CHAR *s)
{
    errno = 0;
    CHAR *ret = strdup(s);
    if (NULL == ret) {
        const INT32 _errno = errno;
        evo_loge(EVOWRAPPER_STRDUP, "%s", strerror(_errno));
    }
    return ret;
}

CHAR* evo_strndup(const CHAR *s, SIZE_T n)
{
    errno = 0;
    CHAR *ret = strndup(s, n);
    if (NULL == ret) {
        const INT32 _errno = errno;
        evo_loge(EVOWRAPPER_STRNDUP, "%s", strerror(_errno));
    }
    return ret;
}

CHAR* evo_strdupa(const CHAR *s)
{
#ifdef _GNU_SOURCE
    return strdupa(s);
#endif

    EVO_UNUSED(s);
    evo_loge(EVOWRAPPER_STRDUPA, "macro %s is needed", "_GNU_SOURCE");
    return NULL;
}

CHAR* evo_strndupa(const CHAR *s, SIZE_T n)
{
#ifdef _GNU_SOURCE
    return strndupa(s, n);
#endif

    EVO_UNUSED(s);
    EVO_UNUSED(n);
    evo_loge(EVOWRAPPER_STRNDUPA, "macro %s is needed", "_GNU_SOURCE");
    return NULL;
}

CHAR* evo_strfry(CHAR *string)
{
#ifdef _GNU_SOURCE
    return strfry(string);
#endif

    EVO_UNUSED(string);
    evo_loge(EVOWRAPPER_STRFRY, "macro %s is needed", "_GNU_SOURCE");
    return NULL;
}

SIZE_T evo_strlen(const CHAR *s)
{
    return strlen(s);
}

SIZE_T evo_strnlen(const CHAR *s, SIZE_T maxlen)
{
    return strnlen(s, maxlen);
}

SIZE_T evo_wcslen(const WCHAR *s)
{
    return wcslen(s);
}

SIZE_T evo_wcsnlen(const WCHAR *s, SIZE_T maxlen)
{
    return wcsnlen(s, maxlen);
}

CHAR* evo_strpbrk(const CHAR *s, const CHAR *accept)
{
    return strpbrk(s, accept);
}

CHAR* evo_strsep(CHAR **stringp, const CHAR *delim)
{
    return strsep(stringp, delim);
}

CHAR* evo_strstr(const CHAR *haystack, const CHAR *needle)
{
    return strstr(haystack, needle);
}

CHAR* evo_strcasestr(const CHAR *haystack, const CHAR *needle)
{
#ifdef _GNU_SOURCE
    return strcasestr(haystack, needle);
#endif

    EVO_UNUSED(haystack);
    EVO_UNUSED(needle);
    evo_loge(EVOWRAPPER_STRCASESTR, "macro %s is needed", "_GNU_SOURCE");
    return NULL;
}

CHAR* evo_strtok(CHAR *s, const CHAR *delim)
{
    return strtok(s, delim);
}

CHAR* evo_strtok_r(CHAR *s, const CHAR *delim, CHAR **saveptr)
{
    return strtok_r(s, delim, saveptr);
}

SIZE_T evo_strxfrm(CHAR *dest, const CHAR *src, SIZE_T n)
{
    return strxfrm(dest, src, n);
}

INT32 evo_strcasecmp(const CHAR *s1, const CHAR *s2)
{
    return strcasecmp(s1, s2);
}

INT32 evo_strncasecmp(const CHAR *s1, const CHAR *s2, SIZE_T n)
{
    return strncasecmp(s1, s2, n);
}

CHAR* evo_index(const CHAR *s, INT32 c)
{
    return index(s, c);
}

CHAR* evo_rindex(const CHAR *s, INT32 c)
{
    return rindex(s, c);
}

/**************************************************/

INT32 evo_atoi(const CHAR *nptr)
{
    return atoi(nptr);
}

LONG evo_atol(const CHAR *nptr)
{
    return atol(nptr);
}

LLONG evo_atoll(const CHAR *nptr)
{
    return atoll(nptr);
}

DOUBLE evo_atof(const CHAR *nptr)
{
    return atof(nptr);
}

DOUBLE evo_strtod(const CHAR *nptr, CHAR **endptr)
{
    errno = 0;
    DOUBLE ret = strtod(nptr, endptr);
    if (ERANGE == errno) {
        const INT32 _errno = errno;
        evo_loge(EVOWRAPPER_STRTOD, "strtod %s", strerror(_errno));
    }
    return ret;
}

FLOAT evo_strtof(const CHAR *nptr, CHAR **endptr)
{
    errno = 0;
    FLOAT ret = strtof(nptr, endptr);
    if (ERANGE == errno) {
        const INT32 _errno = errno;
        evo_loge(EVOWRAPPER_STRTOF, "strtof %s", strerror(_errno));
    }
    return ret;
}

LDOUBLE evo_strtold(const CHAR *nptr, CHAR **endptr)
{
    errno = 0;
    LDOUBLE ret = strtold(nptr, endptr);
    if (ERANGE == errno) {
        const INT32 _errno = errno;
        evo_loge(EVOWRAPPER_STRTOLD, "strtold %s", strerror(_errno));
    }
    return ret;
}

LONG evo_strtol(const CHAR *nptr, CHAR **endptr, INT32 base)
{
    errno = 0;
    LONG ret = strtol(nptr, endptr, base);
    if (ERANGE == errno || EINVAL == errno) {
        const INT32 _errno = errno;
        evo_loge(EVOWRAPPER_STRTOL, "strtol %s", strerror(_errno));
    }
    return ret;
}

LLONG evo_strtoll(const CHAR *nptr, CHAR **endptr, INT32 base)
{
    errno = 0;
    LLONG ret = strtoll(nptr, endptr, base);
    if (ERANGE == errno || EINVAL == errno) {
        const INT32 _errno = errno;
        evo_loge(EVOWRAPPER_STRTOLL, "strtoll %s", strerror(_errno));
    }
    return ret;
}

ULONG evo_strtoul(const CHAR *nptr, CHAR **endptr, INT32 base)
{
    errno = 0;
    ULONG ret = strtoul(nptr, endptr, base);
    if (ERANGE == errno || EINVAL == errno) {
        const INT32 _errno = errno;
        evo_loge(EVOWRAPPER_STRTOUL, "strtoul %s", strerror(_errno));
    }
    return ret;
}

ULLONG evo_strtoull(const CHAR *nptr, CHAR **endptr, INT32 base)
{
    errno = 0;
    ULLONG ret = strtoull(nptr, endptr, base);
    if (ERANGE == errno || EINVAL == errno) {
        const INT32 _errno = errno;
        evo_loge(EVOWRAPPER_STRTOULL, "strtoull %s", strerror(_errno));
    }
    return ret;
}

/**************************************************/

VOID* evo_memset(VOID *s, INT32 c, SIZE_T n)
{
    return memset(s, c, n);
}

WCHAR* evo_wmemset(WCHAR *wcs, WCHAR wc, SIZE_T n)
{
    return wmemset(wcs, wc, n);
}

VOID evo_bzero(VOID *s, SIZE_T n)
{
    bzero(s, n);
}

VOID evo_swab(const VOID *from, VOID *to, SSIZE_T n)
{
#ifndef _XOPEN_SOURCE
    evo_loge(EVOWRAPPER_SWAB, "macro %s is needed", "_XOPEN_SOURCE");
    return;
#endif

    swab(from, to, n);
}

/**************************************************/

INT32 evo_open(const CHAR *pathname, INT32 flags)
{
    errno = 0;
    INT32 ret = open(pathname, flags);
    if (-1 == ret) {
        const INT32 _errno = errno;
        evo_loge(EVOWRAPPER_OPEN, "%s", strerror(_errno));
    }
    return ret;
}

INT32 evo_create(const CHAR *pathname, INT32 flags, MODE_T mode)
{
    errno = 0;
    INT32 ret = open(pathname, flags, mode);
    if (-1 == ret) {
        const INT32 _errno = errno;
        evo_loge(EVOWRAPPER_CREATE, "%s", strerror(_errno));
    }
    return ret;
}

OFF_T evo_lseek(INT32 fd, OFF_T offset, INT32 whence)
{
    errno = 0;
    INT32 ret = lseek(fd, offset, whence);
    if (-1 == ret) {
        const INT32 _errno = errno;
        evo_loge(EVOWRAPPER_LSEEK, "%s", strerror(_errno));
    }
    return ret;
}

SSIZE_T evo_write(INT32 fd, const VOID *buf, SIZE_T count)
{
    errno = 0;
    INT32 ret = write(fd, buf, count);
    if (-1 == ret) {
        const INT32 _errno = errno;
        evo_loge(EVOWRAPPER_WRITE, "%s", strerror(_errno));
    }
    return ret;
}

SSIZE_T evo_read(INT32 fd, VOID *buf, SIZE_T count)
{
    errno = 0;
    INT32 ret = read(fd, buf, count);
    if (-1 == ret) {
        const INT32 _errno = errno;
        evo_loge(EVOWRAPPER_READ, "%s", strerror(_errno));
    }
    return ret;
}

INT32 evo_close(INT32 fd)
{
    errno = 0;
    INT32 ret = close(fd);
    if (-1 == ret) {
        const INT32 _errno = errno;
        evo_loge(EVOWRAPPER_CLOSE, "%s", strerror(_errno));
    }
    return ret;
}

INT32 evo_safe_write(INT32 fd, const CHAR *buf, INT32 count)
{
    INT32 size = 0;
    while (count > 0) {
        errno = 0;
        INT32 ret = write(fd, buf, count);
        if (-1 == ret) {
            if (EAGAIN == errno || EINTR == errno) {
                continue;
            }
            else {
                return (0 == size) ? -1 : size;
            }
        }
        else if (0 == ret) {
            return size;
        }
        buf += ret;
        size += ret;
        count -= ret;
    }
    return size;
}

INT32 evo_safe_read(INT32 fd, CHAR *buf, INT32 count)
{
    INT32 size = 0;
    while (count > 0) {
        INT32 ret = read(fd, buf, count);
        if (-1 == ret) {
            if (EAGAIN == errno || EINTR == errno) {
                continue;
            }
            else {
                return (0 == size) ? -1 : size;
            }
        }
        else if (0 == ret) {
            return size;
        }
        buf += ret;
        size += ret;
        count -= ret;
    }
    return size;
}

INT32 evo_fcntl(INT32 fd, INT32 cmd)
{
    errno = 0;
    INT32 ret = fcntl(fd, cmd);
    if (-1 == ret) {
        const INT32 _errno = errno;
        evo_loge(EVOWRAPPER_FCNTL, "%s", strerror(_errno));
    }
    return ret;
}

INT32 evo_fcntl_int(INT32 fd, INT32 cmd, INT32 arg)
{
    errno = 0;
    INT32 ret = fcntl(fd, cmd, arg);
    if (-1 == ret) {
        const INT32 _errno = errno;
        evo_loge(EVOWRAPPER_FCNTL_INT, "%s", strerror(_errno));
    }
    return ret;
}

INT32 evo_fcntl_flock(INT32 fd, INT32 cmd, struct flock *arg)
{
    errno = 0;
    INT32 ret = fcntl(fd, cmd, arg);
    if (-1 == ret) {
        const INT32 _errno = errno;
        evo_loge(EVOWRAPPER_FCNTL_FLOCK, "%s", strerror(_errno));
    }
    return ret;
}

INT32 evo_socketpair(INT32 domain, INT32 type, INT32 protocol, INT32 sv[2])
{
    errno = 0;
    INT32 ret = socketpair(domain, type, protocol, sv);
    if (-1 == ret) {
        const INT32 _errno = errno;
        evo_loge(EVOWRAPPER_SOCKETPAIR, "%s", strerror(_errno));
    }
    return ret;
}

INT32 evo_select(INT32 nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout)
{
    errno = 0;
    INT32 ret = select(nfds, readfds, writefds, exceptfds, timeout);
    if (-1 == ret) {
        const INT32 _errno = errno;
        evo_loge(EVOWRAPPER_SELECT, "%s", strerror(_errno));
    }
    return ret;
}

/**************************************************/

PID_T evo_getpid()
{
    return getpid();
}

PID_T evo_getppid()
{
    return getppid();
}

PID_T evo_gettid()
{
#ifndef _GNU_SOURCE
    evo_loge(EVOWRAPPER_SYSCALL, "macro %s is needed", "_GNU_SOURCE");
    return -1;
#endif

    errno = 0;
    INT32 ret = syscall(EVOWRAPPER_GETTID);
    if (-1 == ret) {
        const INT32 _errno = errno;
        evo_loge(EVOWRAPPER_SYSCALL, "gettid %s", strerror(_errno));
    }
    return ret;
}

UID_T evo_getuid()
{
    return getuid();
}

UID_T evo_geteuid()
{
    return geteuid();
}

INT32 evo_setuid(UID_T uid)
{
    errno = 0;
    INT32 ret = setuid(uid);
    if (-1 == ret) {
         const INT32 _errno = errno;
         evo_loge(EVOWRAPPER_SETUID, "%s", strerror(_errno));
    }
    return ret;
}

INT32 evo_seteuid(UID_T euid)
{
    errno = 0;
    INT32 ret = seteuid(euid);
    if (-1 == ret) {
         const INT32 _errno = errno;
         evo_loge(EVOWRAPPER_SETEUID, "%s", strerror(_errno));
    }
    return ret;
}

GID_T evo_getgid()
{
    return getgid();
}

GID_T evo_getegid()
{
    return getegid();
}

INT32 evo_setgid(GID_T gid)
{
    errno = 0;
    INT32 ret = setgid(gid);
    if (-1 == ret) {
         const INT32 _errno = errno;
         evo_loge(EVOWRAPPER_SETGID, "%s", strerror(_errno));
    }
    return ret;
}

INT32 evo_setegid(UID_T egid)
{
    errno = 0;
    INT32 ret = setegid(egid);
    if (-1 == ret) {
         const INT32 _errno = errno;
         evo_loge(EVOWRAPPER_SETEGID, "%s", strerror(_errno));
    }
    return ret;
}

PID_T evo_getpgid(PID_T pid)
{
    errno = 0;
    PID_T ret = getpgid(pid);
    if (-1 == ret) {
         const INT32 _errno = errno;
         evo_loge(EVOWRAPPER_GETPGID, "%s", strerror(_errno));
    }
    return ret;
}

INT32 evo_setpgid(PID_T pid, PID_T pgid)
{
    errno = 0;
    PID_T ret = setpgid(pid, pgid);
    if (-1 == ret) {
         const INT32 _errno = errno;
         evo_loge(EVOWRAPPER_SETPGID, "%s", strerror(_errno));
    }
    return ret;
}

/**************************************************/

UINT32 evo_sleep(UINT32 seconds)
{
    return sleep(seconds);
}

SigHandler evo_signal(INT32 signum, SigHandler handler)
{
    errno = 0;
    SigHandler ret = signal(signum,handler);
    if (SIG_ERR == ret) {
        const INT32 _errno = errno;
        evo_loge(EVOWARPPER_SIGNAL, "%s", strerror(_errno));
    }
    return ret;
}

INT32 evo_sigaction(INT32 sig, const struct sigaction *act, struct sigaction *oact)
{
    errno = 0;
    INT32 ret = sigaction(sig, act, oact);
    if (-1 == ret) {
        const INT32 _errno = errno;
        evo_loge(EVOWRAPPER_SIGACTION, "%s", strerror(_errno));
    }
    return ret;
}

INT32 evo_kill(PID_T pid, INT32 sig)
{
    errno = 0;
    INT32 ret = kill(pid, sig);
    if (-1 == ret) {
        const INT32 _errno = errno;
        evo_loge(EVOWRAPPER_KILL, "%s", strerror(_errno));
    }
    return ret;
}

INT32 evo_raise(INT32 sig)
{
    INT32 ret = raise(sig);
    if (0 != ret) {
        evo_loge(EVOWRAPPER_RAISE, "raise %d error", sig);
    }
    return ret;
}

VOID evo_exit(INT32 status)
{
    exit(status);
}

PID_T evo_fork()
{
    errno = 0;
    PID_T ret = fork();
    if (-1 == ret) {
        const INT32 _errno = errno;
        evo_loge(EVOWRAPPER_FORK, "%s", strerror(_errno));
    }
    return ret;
}

PID_T evo_waitpid(PID_T pid, INT32 *status, INT32 options)
{
    errno = 0;
    PID_T ret = waitpid(pid, status, options);
    if (-1 == ret) {
        const INT32 _errno = errno;
        evo_loge(EVOWRAPPER_WAITPID, "%s", strerror(_errno));
    }
    return ret;
}

INT32 evo_execl(const CHAR *path, const CHAR *arg, ...)
{
    CHAR *param_buf = (CHAR*)malloc(EVOWRAPPER_PARAM_BUFSIZ);
    ASSERT(NULL != param_buf);
    CHAR *params[EVOWRAPPER_PARAM_MAX] = { 0 };
    INT32 param_count = 0;
    INT32 param_totalsize = 0;
    va_list args;
    va_start(args, arg);
    while (1) {
       CHAR *tmp = va_arg(args, CHAR*);
       if (strcmp(EVOWRAPPER_PARAM_SENTINEL, tmp) == 0) {
           break;
       }
       INT32 len = strlen(tmp);
       ASSERT(EVOWRAPPER_PARAM_LEN > len);
       strncpy(param_buf + param_totalsize, tmp, len + 1);
       params[param_count++] = param_buf + param_totalsize;
       ASSERT(EVOWRAPPER_PARAM_MAX >= param_count);
       param_totalsize += (len + 1);
       ASSERT(EVOWRAPPER_PARAM_BUFSIZ >= param_totalsize);
    }
    va_end(args);

    INT32 ret = -1;
    errno = 0;
    if (0 == param_count) {
        ret = execl(path, arg, NULL);
    }
    else if (1 == param_count) {
        ret = execl(path, arg, params[0], NULL);
    }
    else if (2 == param_count) {
        ret = execl(path, arg, params[0], params[1], NULL);
    }
    else if (3 == param_count) {
        ret = execl(path, arg, params[0], params[1], params[2], NULL);
    }
    else {
        ret = execl(path, arg, params[0], params[1], params[2], params[3], NULL);
    }

    if (-1 == ret) {
        const INT32 _errno = errno;
        evo_loge(EVOWRAPPER_EXECL, "%s", strerror(_errno));
    }

    free(param_buf);

    return ret;
}

/**************************************************/

MQD_T evo_mq_open(const CHAR *name, INT32 oflag)
{
    errno = 0;
    MQD_T ret = mq_open(name, oflag);
    if (-1 == ret) {
        const INT32 _errno = errno;
        evo_loge(EVOWRAPPER_POSIX_MQ_OPEN, "%s", strerror(_errno));
    }
    return ret;
}

MQD_T evo_mq_create(const CHAR *name, INT32 oflag, MODE_T mode, struct mq_attr *attr)
{
    errno = 0;
    MQD_T ret = mq_open(name, oflag, mode, attr);
    if (-1 == ret) {
        const INT32 _errno = errno;
        evo_loge(EVOWRAPPER_POSIX_MQ_CREATE, "%s", strerror(_errno));
    }
    return ret;
}

INT32 evo_mq_close(MQD_T mqdes)
{
    errno = 0;
    INT32 ret = mq_close(mqdes);
    if (-1 == ret) {
        const INT32 _errno = errno;
        evo_loge(EVOWRAPPER_POSIX_MQ_CLOSE, "%s", strerror(_errno));
    }
    return ret;
}

INT32 evo_mq_unlink(const CHAR *name)
{
    errno = 0;
    INT32 ret = mq_unlink(name);
    if (-1 == ret) {
        const INT32 _errno = errno;
        evo_loge(EVOWRAPPER_POSIX_MQ_UNLINK, "%s", strerror(_errno));
    }
    return ret;
}

INT32 evo_mq_getattr(MQD_T mqdes, struct mq_attr *attr)
{
    errno = 0;
    INT32 ret = mq_getattr(mqdes, attr);
    if (-1 == ret) {
        const INT32 _errno = errno;
        evo_loge(EVOWRAPPER_POSIX_MQ_GETATTR, "%s", strerror(_errno));
    }
    return ret;
}

INT32 evo_mq_setattr(MQD_T mqdes, const struct mq_attr *newattr, struct mq_attr *oldattr)
{
    errno = 0;
    INT32 ret = mq_setattr(mqdes, newattr, oldattr);
    if (-1 == ret) {
        const INT32 _errno = errno;
        evo_loge(EVOWRAPPER_POSIX_MQ_SETATTR, "%s", strerror(_errno));
    }
    return ret;
}

INT32 evo_mq_send(MQD_T mqdes, const CHAR *msg_ptr, SIZE_T msg_len, UINT32 msg_prio)
{
    errno = 0;
    INT32 ret = mq_send(mqdes, msg_ptr, msg_len, msg_prio);
    if (-1 == ret) {
        const INT32 _errno = errno;
        evo_loge(EVOWRAPPER_POSIX_MQ_SEND, "%s", strerror(_errno));
    }
    return ret;
}

SSIZE_T evo_mq_receive(MQD_T mqdes, CHAR *msg_ptr, SIZE_T msg_len, UINT32 *msg_prio)
{
    errno = 0;
    SSIZE_T ret = mq_receive(mqdes, msg_ptr, msg_len, msg_prio);
    if (-1 == ret) {
        const INT32 _errno = errno;
        evo_loge(EVOWRAPPER_POSIX_MQ_RECEIVE, "%s", strerror(_errno));
    }
    return ret;
}

INT32 evo_mq_notify(MQD_T mqdes, const struct sigevent *sevp)
{
    errno = 0;
    INT32 ret = mq_notify(mqdes, sevp);
    if (-1 == ret) {
        const INT32 _errno = errno;
        evo_loge(EVOWRAPPER_POSIX_MQ_NOTIFY, "%s", strerror(_errno));
    }
    return ret;
}

/**************************************************/

INT32 evo_pthread_create(TID_T *thread, const pthread_attr_t *attr, thread_routine p, VOID *arg)
{
    INT32 ret = pthread_create(thread, attr, p, arg);
    if (0 != ret) {
        evo_loge(EVOWRAPPER_PTHREAD_CREATE, "%s", strerror(ret));
    }
    return ret;
}

VOID evo_pthread_exit(VOID *value_ptr)
{
    pthread_exit(value_ptr);
}

INT32 evo_pthread_join(TID_T thread, VOID **retval)
{
    INT32 ret = pthread_join(thread, retval);
    if (0 != ret) {
        evo_loge(EVOWRAPPER_PTHREAD_JOIN, "%s", strerror(ret));
    }
    return ret;
}

INT32 evo_pthread_cancel(TID_T thread)
{
    INT32 ret = pthread_cancel(thread);
    if (0 != ret) {
        evo_loge(EVOWRAPPER_PTHREAD_CANCEL, "%s", strerror(ret));
    }
    return ret;
}

INT32 evo_pthread_detach(TID_T thread)
{
    INT32 ret = pthread_detach(thread);
    if (0 != ret) {
        evo_loge(EVOWRAPPER_PTHREAD_DETACH, "%s", strerror(ret));
    }
    return ret;
}

TID_T evo_pthread_self()
{
    return pthread_self();
}

INT32 evo_pthread_kill(TID_T thread, INT32 sig)
{
    INT32 ret = pthread_kill(thread, sig);
    if (0 != ret) {
        evo_loge(EVOWRAPPER_PTHREAD_KILL, "%s", strerror(ret));
    }
    return ret;
}

INT32 evo_pthread_equal(TID_T t1, TID_T t2)
{
    return pthread_equal(t1, t2);
}

INT32 evo_getconcurrency()
{
    return pthread_getconcurrency();
}

INT32 evo_setconcurrency(INT32 new_level)
{
    INT32 ret = pthread_setconcurrency(new_level);
    if (0 != ret) {
        evo_loge(EVOWRAPPER_PTHREAD_SETCONCURRENCY, "%s", strerror(ret));
    }
    return ret;
}

/**************************************************/

INT32 evo_pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr)
{
    INT32 ret = pthread_mutex_init(mutex, attr);
    if (0 != ret) {
        evo_loge(EVOWRAPPER_PTHREAD_MUTEX_INIT, "%s", strerror(ret));
    }
    return ret;
}

INT32 evo_pthread_mutex_destroy(pthread_mutex_t *mutex)
{
    INT32 ret = pthread_mutex_destroy(mutex);
    if (0 != ret) {
        evo_loge(EVOWRAPPER_PTHREAD_MUTEX_DESTROY, "%s", strerror(ret));
    }
    return ret;
}

INT32 evo_pthread_mutex_trylock(pthread_mutex_t *mutex)
{
    INT32 ret = pthread_mutex_trylock(mutex);
    if (0 != ret) {
        evo_loge(EVOWRAPPER_PTHREAD_MUTEX_TRYLOCK, "%s", strerror(ret));
    }
    return ret;
}

INT32 evo_pthread_mutex_lock(pthread_mutex_t *mutex)
{
    INT32 ret = pthread_mutex_lock(mutex);
    if (0 != ret) {
        evo_loge(EVOWRAPPER_PTHREAD_MUTEX_LOCK, "%s", strerror(ret));
    }
    return ret;
}

INT32 evo_pthread_mutex_timedlock(pthread_mutex_t *mutex, const struct timespec *abstime)
{
#ifndef  _GNU_SOURCE
    evo_loge(EVOWRAPPER_PTHREAD_MUTEX_TIMEDLOCK, "pthread_mutex_timedlock not supported");
    return -1;
#endif

    INT32 ret = pthread_mutex_timedlock(mutex, abstime);
    if (0 != ret) {
        evo_loge(EVOWRAPPER_PTHREAD_MUTEX_TIMEDLOCK, "%s", strerror(ret));
    }
    return ret;
}

INT32 evo_pthread_mutex_unlock(pthread_mutex_t *mutex)
{
    INT32 ret = pthread_mutex_unlock(mutex);
    if (0 != ret) {
        evo_loge(EVOWRAPPER_PTHREAD_MUTEX_UNLOCK, "%s", strerror(ret));
    }
    return ret;
}

INT32 evo_pthread_mutexattr_init(pthread_mutexattr_t *attr)
{
    INT32 ret = pthread_mutexattr_init(attr);
    if (0 != ret) {
        evo_loge(EVOWRAPPER_PTHREAD_MUTEXATTR_INIT, "%s", strerror(ret));
    }
    return ret;
}

INT32 evo_pthread_mutexattr_destroy(pthread_mutexattr_t *attr)
{
    INT32 ret = pthread_mutexattr_destroy(attr);
    if (0 != ret) {
        evo_loge(EVOWRAPPER_PTHREAD_MUTEXATTR_DESTROY, "%s", strerror(ret));
    }
    return ret;
}

INT32 evo_pthread_mutexattr_setpshared(pthread_mutexattr_t *attr, INT32 pshared)
{
    INT32 ret = pthread_mutexattr_setpshared(attr, pshared);
    if (0 != ret) {
        evo_loge(EVOWRAPPER_PTHREAD_MUTEXATTR_SETPSHARED, "%s", strerror(ret));
    }
    return ret;
}

/**************************************************/

INT32 evo_pthread_cond_init(pthread_cond_t *cond, const pthread_condattr_t *cond_attr)
{
    INT32 ret = pthread_cond_init(cond, cond_attr);
    if (0 != ret) {
        evo_loge(EVOWRAPPER_PTHREAD_COND_INIT, "%s", strerror(ret));
    }
    return ret;
}

INT32 evo_pthread_cond_destroy(pthread_cond_t *cond)
{
    INT32 ret = pthread_cond_destroy(cond);
    if (0 != ret) {
        evo_loge(EVOWRAPPER_PTHREAD_COND_DESTROY, "%s", strerror(ret));
    }
    return ret;
}

INT32 evo_pthread_cond_signal(pthread_cond_t *cond)
{
    INT32 ret = pthread_cond_signal(cond);
    if (0 != ret) {
        evo_loge(EVOWRAPPER_PTHREAD_COND_SIGNAL, "%s", strerror(ret));
    }
    return ret;
}

INT32 evo_pthread_cond_broadcast(pthread_cond_t *cond)
{
    INT32 ret = pthread_cond_broadcast(cond);
    if (0 != ret) {
        evo_loge(EVOWRAPPER_PTHREAD_COND_BROADCAST, "%s", strerror(ret));
    }
    return ret;
}

INT32 evo_pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex)
{
    INT32 ret = pthread_cond_wait(cond, mutex);
    if (0 != ret) {
        evo_loge(EVOWRAPPER_PTHREAD_COND_WAIT, "%s", strerror(ret));
    }
    return ret;
}

INT32 evo_pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex, const struct timespec *abstime)
{
    INT32 ret = pthread_cond_timedwait(cond, mutex, abstime);
    if (0 != ret) {
        evo_loge(EVOWRAPPER_PTHREAD_COND_TIMEDWAIT, "%s", strerror(ret));
    }
    return ret;
}

INT32 evo_pthread_condattr_init(pthread_condattr_t *attr)
{
    INT32 ret = pthread_condattr_init(attr);
    if (0 != ret) {
        evo_loge(EVOWRAPPER_PTHREAD_CONDATTR_INIT, "%s", strerror(ret));
    }
    return ret;
}

INT32 evo_pthread_condattr_destroy(pthread_condattr_t *attr)
{
    INT32 ret = pthread_condattr_destroy(attr);
    if (0 != ret) {
        evo_loge(EVOWRAPPER_PTHREAD_CONDATTR_DESTROY, "%s", strerror(ret));
    }
    return ret;
}

INT32 evo_pthread_condattr_setpshared(pthread_condattr_t *attr, INT32 pshared)
{
    INT32 ret = pthread_condattr_setpshared(attr, pshared);
    if (0 != ret) {
        evo_loge(EVOWRAPPER_PTHREAD_CONDATTR_SETPSHARED, "%s", strerror(ret));
    }
    return ret;
}

/**************************************************/

INT32 evo_pthread_rwlock_init(pthread_rwlock_t *rwlock, const pthread_rwlockattr_t *attr)
{
    INT32 ret = pthread_rwlock_init(rwlock, attr);
    if (0 != ret) {
        evo_loge(EVOWRAPPER_PTHREAD_RWLOCK_INIT, "%s", strerror(ret));
    }
    return ret;
}

INT32 evo_pthread_rwlock_destroy(pthread_rwlock_t *rwlock)
{
    INT32 ret = pthread_rwlock_destroy(rwlock);
    if (0 != ret) {
        evo_loge(EVOWRAPPER_PTHREAD_RWLOCK_DESTROY, "%s", strerror(ret));
    }
    return ret;
}

INT32 evo_pthread_rwlock_rdlock(pthread_rwlock_t *rwlock)
{
    INT32 ret = pthread_rwlock_rdlock(rwlock);
    if (0 != ret) {
        evo_loge(EVOWRAPPER_PTHREAD_RWLOCK_RDLOCK, "%s", strerror(ret));
    }
    return ret;
}

INT32 evo_pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock)
{
    INT32 ret = pthread_rwlock_tryrdlock(rwlock);
    if (0 != ret) {
        evo_loge(EVOWRAPPER_PTHREAD_RWLOCK_TRYRDLOCK, "%s", strerror(ret));
    }
    return ret;
}

INT32 evo_pthread_rwlock_wrlock(pthread_rwlock_t *rwlock)
{
    INT32 ret = pthread_rwlock_wrlock(rwlock);
    if (0 != ret) {
        evo_loge(EVOWRAPPER_PTHREAD_RWLOCK_WRLOCK, "%s", strerror(ret));
    }
    return ret;
}

INT32 evo_pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock)
{
    INT32 ret = pthread_rwlock_trywrlock(rwlock);
    if (0 != ret) {
        evo_loge(EVOWRAPPER_PTHREAD_RWLOCK_TRYWRLOCK, "%s", strerror(ret));
    }
    return ret;
}

INT32 evo_pthread_rwlock_unlock(pthread_rwlock_t *rwlock)
{
    INT32 ret = pthread_rwlock_unlock(rwlock);
    if (0 != ret) {
        evo_loge(EVOWRAPPER_PTHREAD_RWLOCK_UNLOCK, "%s", strerror(ret));
    }
    return ret;
}

INT32 evo_pthread_rwlockattr_init(pthread_rwlockattr_t *attr)
{
    INT32 ret = pthread_rwlockattr_init(attr);
    if (0 != ret) {
        evo_loge(EVOWRAPPER_PTHREAD_RWLOCKATTR_INIT, "%s", strerror(ret));
    }
    return ret;
}

INT32 evo_pthread_rwlockattr_destroy(pthread_rwlockattr_t *attr)
{
    INT32 ret = pthread_rwlockattr_destroy(attr);
    if (0 != ret) {
        evo_loge(EVOWRAPPER_PTHREAD_RWLOCKATTR_DESTROY, "%s", strerror(ret));
    }
    return ret;
}

INT32 evo_pthread_rwlockattr_setpshared(pthread_rwlockattr_t *attr, INT32 pshared)
{
    INT32 ret = pthread_rwlockattr_setpshared(attr, pshared);
    if (0 != ret) {
        evo_loge(EVOWRAPPER_PTHREAD_RWLOCKATTR_SETPSHARED, "%s", strerror(ret));
    }
    return ret;
}

/**************************************************/

INT32 evo_pthread_spin_init(pthread_spinlock_t *lock, INT32 pshared)
{
    INT32 ret = pthread_spin_init(lock, pshared);
    if (0 != ret) {
        evo_loge(EVOWRAPPER_PTHREAD_SPINLOCK_INIT, "pthread_spin_init error");
    }
    return ret;
}

INT32 evo_pthread_spin_destroy(pthread_spinlock_t *lock)
{
    INT32 ret = pthread_spin_destroy(lock);
    if (0 != ret) {
        evo_loge(EVOWRAPPER_PTHREAD_SPINLOCK_DESTROY, "pthread_spin_destroy error");
    }
    return ret;
}

INT32 evo_pthread_spin_lock(pthread_spinlock_t *lock)
{
    INT32 ret = pthread_spin_lock(lock);
    if (0 != ret) {
        evo_loge(EVOWRAPPER_PTHREAD_SPINLOCK_LOCK, "pthread_spin_lock error");
    }
    return ret;
}

INT32 evo_pthread_spin_trylock(pthread_spinlock_t *lock)
{
    INT32 ret = pthread_spin_trylock(lock);
    if (0 != ret) {
        evo_loge(EVOWRAPPER_PTHREAD_SPINLOCK_TRYLOCK, "pthread_spin_trylock error");
    }
    return ret;
}

INT32 evo_pthread_spin_unlock(pthread_spinlock_t *lock)
{
    INT32 ret = pthread_spin_unlock(lock);
    if (0 != ret) {
        evo_loge(EVOWRAPPER_PTHREAD_SPINLOCK_UNLOCK, "pthread_spin_unlock error");
    }
    return ret;
}

/**************************************************/

INT32 evo_pthread_barrier_init(pthread_barrier_t *barrier, const pthread_barrierattr_t *attr, UINT32 count)
{
    return pthread_barrier_init(barrier, attr, count);
}

INT32 evo_pthread_barrier_destroy(pthread_barrier_t *barrier)
{
    return pthread_barrier_destroy(barrier);
}

INT32 evo_pthread_barrier_wait(pthread_barrier_t *barrier)
{
    return pthread_barrier_wait(barrier);;
}

/**************************************************/

VOID* evo_dlopen(const CHAR *filename, INT32 flag)
{
    dlerror();
    VOID* ret = dlopen(filename, flag);
    if (NULL == ret) {
        evo_loge(EVOWRAPPER_DLOPEN, "%s", dlerror());
    }
    return ret;
}

VOID* evo_dlsym(VOID *handle, const CHAR *symbol)
{
    dlerror();
    VOID* ret = dlsym(handle, symbol);
    if (NULL == ret) {
        evo_loge(EVOWRAPPER_DLSYM, "%s", dlerror());
    }
    return ret;
}

INT32 evo_dlclose(VOID *handle)
{
    dlerror();
    INT32 ret = dlclose(handle);
    if (0 != ret) {
        evo_loge(EVOWRAPPER_DLCLOSE, "%s", dlerror());
    }
    return ret;
}

INT32 evo_dladdr(const VOID *address, VOID *info)
{
#ifndef _GNU_SOURCE
    evo_loge(EVOWRAPPER_DLADDR, "macro %s is needed", "_GNU_SOURCE");
    return -1;
#endif

    INT32 ret = dladdr(address, (Dl_info*)info);
    if (0 == ret) {
        evo_loge(EVOWRAPPER_DLADDR, "no shared object's segments contain that address");
    }
    return ret;
}
