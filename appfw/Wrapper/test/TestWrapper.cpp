#include <cstdio>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <dlfcn.h>
#include <sys/socket.h>
#include <sys/auxv.h>
#include <mqueue.h>

#include "log/Log.h"
#include "wrapper/Wrapper.h"
#include "TestWrapper.h"

#define TestWrapperTag "TestWrapper"

TestWrapper::TestWrapper()
    : ETestSuite(TestWrapperTag)
{
}

TestWrapper::~TestWrapper()
{
}

VOID TestWrapper::run()
{
    test_env();
    test_string();
    test_string_number();
    test_mem();
    test_fd();
    test_id();
    test_process();
    test_posix_mq();
    test_pthread();
    test_pthread_mutex();
    test_pthread_condition();
    test_pthread_rwlock();
    test_pthread_spinlock();
    test_pthread_barrier();
    test_dl();
}

VOID TestWrapper::test_env()
{
    const CHAR *_env = "wrapper";
    const CHAR *_env2 = "wrapper2";
    const CHAR *_value = "evo";
    const CHAR *_value2 = "evo2";

    CHAR _env2_value[] = "wrapper2=evo";
    CHAR _env2_value2[] = "wrapper2=evo2";
    CHAR _env2_space[] = "wrapper2=";
    CHAR _env2_null[] = "wrapper2";

    evo_logd(TestWrapperTag, "TestWrapper::test_env initial");
    evo_logd(TestWrapperTag, "TestWrapper::test_env %s=%s %s=%s", _env, evo_getenv(_env), _env2, evo_getenv(_env2));
    evo_logd(TestWrapperTag, "TestWrapper::test_env secure %s=%s %s=%s", _env, evo_secure_getenv(_env), _env2, evo_secure_getenv(_env2));

    evo_putenv(_env2_value);
    evo_logd(TestWrapperTag, "TestWrapper::test_env putenv(%s)", _env2_value);
    evo_logd(TestWrapperTag, "TestWrapper::test_env %s=%s %s=%s", _env, evo_getenv(_env), _env2, evo_getenv(_env2));
    evo_logd(TestWrapperTag, "TestWrapper::test_env secure %s=%s %s=%s", _env, evo_secure_getenv(_env), _env2, evo_secure_getenv(_env2));

    evo_putenv(_env2_value2);
    evo_logd(TestWrapperTag, "TestWrapper::test_env putenv(%s)", _env2_value2);
    evo_logd(TestWrapperTag, "TestWrapper::test_env %s=%s %s=%s", _env, evo_getenv(_env), _env2, evo_getenv(_env2));
    evo_logd(TestWrapperTag, "TestWrapper::test_env secure %s=%s %s=%s", _env, evo_secure_getenv(_env), _env2, evo_secure_getenv(_env2));

    evo_putenv(_env2_space);
    evo_logd(TestWrapperTag, "TestWrapper::test_env putenv(%s)", _env2_space);
    evo_logd(TestWrapperTag, "TestWrapper::test_env %s=%s %s=%s", _env, evo_getenv(_env), _env2, evo_getenv(_env2));
    evo_logd(TestWrapperTag, "TestWrapper::test_env secure %s=%s %s=%s", _env, evo_secure_getenv(_env), _env2, evo_secure_getenv(_env2));

    evo_putenv(_env2_null);
    evo_logd(TestWrapperTag, "TestWrapper::test_env putenv(%s)", _env2_null);
    evo_logd(TestWrapperTag, "TestWrapper::test_env %s=%s %s=%s", _env, evo_getenv(_env), _env2, evo_getenv(_env2));
    evo_logd(TestWrapperTag, "TestWrapper::test_env secure %s=%s %s=%s", _env, evo_secure_getenv(_env), _env2, evo_secure_getenv(_env2));

    evo_setenv(_env, _value, 0);
    evo_logd(TestWrapperTag, "TestWrapper::test_env setenv(%s, %s, 0)", _env, _value);
    evo_logd(TestWrapperTag, "TestWrapper::test_env %s=%s %s=%s", _env, evo_getenv(_env), _env2, evo_getenv(_env2));
    evo_logd(TestWrapperTag, "TestWrapper::test_env secure %s=%s %s=%s", _env, evo_secure_getenv(_env), _env2, evo_secure_getenv(_env2));

    evo_setenv(_env, _value2, 0);
    evo_logd(TestWrapperTag, "TestWrapper::test_env setenv(%s, %s, 0)", _env, _value2);
    evo_logd(TestWrapperTag, "TestWrapper::test_env %s=%s %s=%s", _env, evo_getenv(_env), _env2, evo_getenv(_env2));
    evo_logd(TestWrapperTag, "TestWrapper::test_env secure %s=%s %s=%s", _env, evo_secure_getenv(_env), _env2, evo_secure_getenv(_env2));

    evo_setenv(_env, _value2, 1);
    evo_logd(TestWrapperTag, "TestWrapper::test_env setenv(%s, %s, 1)", _env, _value2);
    evo_logd(TestWrapperTag, "TestWrapper::test_env %s=%s %s=%s", _env, evo_getenv(_env), _env2, evo_getenv(_env2));
    evo_logd(TestWrapperTag, "TestWrapper::test_env secure %s=%s %s=%s", _env, evo_secure_getenv(_env), _env2, evo_secure_getenv(_env2));

    evo_unsetenv(_env);
    evo_logd(TestWrapperTag, "TestWrapper::test_env unsetenv(%s)", _env);
    evo_logd(TestWrapperTag, "TestWrapper::test_env %s=%s %s=%s", _env, evo_getenv(_env), _env2, evo_getenv(_env2));
    evo_logd(TestWrapperTag, "TestWrapper::test_env secure %s=%s %s=%s", _env, evo_secure_getenv(_env), _env2, evo_secure_getenv(_env2));

    evo_logd(TestWrapperTag, "TestWrapper::test_env environ");
    extern CHAR **environ;
    ASSERT(NULL != environ);
    CHAR **e = environ;
    INT32 i = 1;
    for (; *e; ++e, ++i) {
        evo_logd(TestWrapperTag, "TestWrapper::test_env environ %d %s", i, *e);
    }

    evo_clearenv();
    evo_logd(TestWrapperTag, "TestWrapper::test_env clearenv");
    ASSERT(NULL == environ);

    evo_logd(TestWrapperTag, "TestWrapper::test_env getauxval");
    evo_logd(TestWrapperTag, "TestWrapper::test_env AT_BASE=%lu", evo_getauxval(AT_BASE));
    evo_logd(TestWrapperTag, "TestWrapper::test_env 0=%lu", evo_getauxval(0));
}

VOID TestWrapper::test_string()
{
    {
        evo_logd(TestWrapperTag, "TestWrapper::test_string stpcpy");
        CHAR buffer[20] = { 0 };
        CHAR *to = buffer;
        to = evo_stpcpy(to, "foo");
        to = evo_stpcpy(to, "bar");
        evo_logd(TestWrapperTag, "TestWrapper::test_string %s", buffer);
    }

    {
        evo_logd(TestWrapperTag, "TestWrapper::test_string strcat");
        const CHAR *src = "foobar";
        CHAR buffer[20] = { 0 };
        buffer[0] = '@';
        evo_logd(TestWrapperTag, "TestWrapper::test_string %s", evo_strcat(buffer, src));
        evo_logd(TestWrapperTag, "TestWrapper::test_string %s", evo_strncat(buffer, src, 3));
        evo_logd(TestWrapperTag, "TestWrapper::test_string %s", buffer);
    }

    {
        evo_logd(TestWrapperTag, "TestWrapper::test_string strchr");
        const CHAR *src = "foobar";
        evo_logd(TestWrapperTag, "TestWrapper::test_string %s", evo_strchr(src, 'o'));
        evo_logd(TestWrapperTag, "TestWrapper::test_string %s", evo_strrchr(src, 'o'));
        evo_logd(TestWrapperTag, "TestWrapper::test_string %p", evo_strchr(src, 'c'));
        evo_logd(TestWrapperTag, "TestWrapper::test_string %p", evo_strchrnul(src, 'c'));
        evo_logd(TestWrapperTag, "TestWrapper::test_string %p", src + 6);
    }

    {
        evo_logd(TestWrapperTag, "TestWrapper::test_string strcmp");
        const CHAR *s1 = "foobar";
        const CHAR *s2 = "foofoo";
        evo_logd(TestWrapperTag, "TestWrapper::test_string %d", evo_strcmp(s1, s2));
        evo_logd(TestWrapperTag, "TestWrapper::test_string %d", evo_strncmp(s1, s2, 3));
    }

    {
        evo_logd(TestWrapperTag, "TestWrapper::test_string strcoll");
        const CHAR *s1 = "foobar";
        const CHAR *s2 = "foofoo";
        evo_logd(TestWrapperTag, "TestWrapper::test_string %d", evo_strcoll(s1, s2));
    }

    {
        evo_logd(TestWrapperTag, "TestWrapper::test_string strcpy");
        const CHAR *src = "foobar";
        const CHAR *src2 = "barfoo";
        CHAR buffer[20] = { 0 };
        buffer[0] = '@';
        evo_logd(TestWrapperTag, "TestWrapper::test_string %s", evo_strcpy(buffer, src));
        evo_logd(TestWrapperTag, "TestWrapper::test_string %s", buffer);
        evo_logd(TestWrapperTag, "TestWrapper::test_string %s", evo_strncpy(buffer, src2, 3));
        evo_logd(TestWrapperTag, "TestWrapper::test_string %s", buffer);
    }

    {
        evo_logd(TestWrapperTag, "TestWrapper::test_string strspn");
        const CHAR *s = "foobar";
        const CHAR *accept = "foob";
        const CHAR *reject = "ba";
        evo_logd(TestWrapperTag, "TestWrapper::test_string %d", evo_strspn(s, accept));
        evo_logd(TestWrapperTag, "TestWrapper::test_string %d", evo_strcspn(s, reject));
    }

    {
        evo_logd(TestWrapperTag, "TestWrapper::test_string strdup");
        const CHAR *s = "foobar";
        CHAR *dup = evo_strdup(s);
        CHAR *ndup = evo_strndup(s, 3);
        evo_logd(TestWrapperTag, "TestWrapper::test_string %s", dup);
        evo_logd(TestWrapperTag, "TestWrapper::test_string %s", ndup);
        evo_logd(TestWrapperTag, "TestWrapper::test_string %s", evo_strdupa(s));
        evo_logd(TestWrapperTag, "TestWrapper::test_string %s", evo_strndupa(s, 3));
        free(dup);
        free(ndup);
    }

    {
        evo_logd(TestWrapperTag, "TestWrapper::test_string strfry");
        CHAR s[] = "foobar";
        evo_logd(TestWrapperTag, "TestWrapper::test_string %s", evo_strfry(s));
        evo_logd(TestWrapperTag, "TestWrapper::test_string %s", s);
    }

    {
        evo_logd(TestWrapperTag, "TestWrapper::test_string strlen");
        const CHAR *s = "foobar";
        const WCHAR *w = L"foobar";
        evo_logd(TestWrapperTag, "TestWrapper::test_string %lu", evo_strlen(s));
        evo_logd(TestWrapperTag, "TestWrapper::test_string %lu", evo_strnlen(s, 3));
        evo_logd(TestWrapperTag, "TestWrapper::test_string %lu", evo_wcslen(w));
        evo_logd(TestWrapperTag, "TestWrapper::test_string %lu", evo_wcsnlen(w, 3));
    }

    {
        evo_logd(TestWrapperTag, "TestWrapper::test_string strpbrk");
        const CHAR *s = "foobar";
        const CHAR *accept = "rf";
        evo_logd(TestWrapperTag, "TestWrapper::test_string %s", evo_strpbrk(s, accept));
    }

    {
        evo_logd(TestWrapperTag, "TestWrapper::test_string strsep");
        CHAR stringp[] = "foo:bar:foo:bar";
        CHAR *buf = stringp;
        const CHAR *delim = ":";
        CHAR *token = NULL;
        while ((token = evo_strsep(&buf, delim)) != NULL) {
            evo_logd(TestWrapperTag, "TestWrapper::test_string %s", token);
        }
    }

    {
        evo_logd(TestWrapperTag, "TestWrapper::test_string strstr");
        const CHAR *haystack = "foobar";
        const CHAR *needle = "oo";
        const CHAR *needle2 = "OO";
        evo_logd(TestWrapperTag, "TestWrapper::test_string %s", evo_strstr(haystack, needle));
        evo_logd(TestWrapperTag, "TestWrapper::test_string %s", evo_strcasestr(haystack, needle));
        evo_logd(TestWrapperTag, "TestWrapper::test_string %s", evo_strstr(haystack, needle2));
        evo_logd(TestWrapperTag, "TestWrapper::test_string %s", evo_strcasestr(haystack, needle2));
    }

    {
        evo_logd(TestWrapperTag, "TestWrapper::test_string strtok");
        CHAR s[] = "foobarhelloworld";
        const CHAR *delim = "o";
        CHAR *token = evo_strtok(s, delim);
        evo_logd(TestWrapperTag, "TestWrapper::test_string %s %s", token, s);
        while ((token = evo_strtok(NULL, delim)) != NULL) {
            evo_logd(TestWrapperTag, "TestWrapper::test_string %s %s", token, s);
        }
        CHAR s2[] = "foobarhelloworld";
        const CHAR *delim2 = "o";
        CHAR saveptr[20] = { 0 };
        CHAR *p = saveptr;
        CHAR *token2 = evo_strtok_r(s2, delim2, &p);
        evo_logd(TestWrapperTag, "TestWrapper::test_string %s %s %s", token2, s2, p);
        while ((token2 = evo_strtok_r(NULL, delim2, &p)) != NULL) {
            evo_logd(TestWrapperTag, "TestWrapper::test_string %s %s %s", token2, s2, p);
        }
    }

    {
        evo_logd(TestWrapperTag, "TestWrapper::test_string strxfrm");
        const CHAR *src = "foobar";
        CHAR dest[20] = { 0 };
        evo_logd(TestWrapperTag, "TestWrapper::test_string %lu %s", evo_strxfrm(dest, src, 4), dest);
    }

    {
        evo_logd(TestWrapperTag, "TestWrapper::test_string strcasecmp");
        const CHAR *s1 = "foobar";
        const CHAR *s2 = "FOObar";
        evo_logd(TestWrapperTag, "TestWrapper::test_string %d", evo_strcasecmp(s1, s2));
        evo_logd(TestWrapperTag, "TestWrapper::test_string %d", evo_strncasecmp(s1, s2, 4));
    }

    {
        evo_logd(TestWrapperTag, "TestWrapper::test_string index");
        const CHAR *s = "foobar";
        INT32 c = 'o';
        evo_logd(TestWrapperTag, "TestWrapper::test_string %s", evo_index(s, c));
        evo_logd(TestWrapperTag, "TestWrapper::test_string %s", evo_rindex(s, c));
    }
}

VOID TestWrapper::test_string_number()
{
    const CHAR *nptr = "1234";
    evo_logd(TestWrapperTag, "TestWrapper::test_string_number a");
    evo_logd(TestWrapperTag, "TestWrapper::test_string_number atoi %d", evo_atoi(nptr));
    evo_logd(TestWrapperTag, "TestWrapper::test_string_number atol %ld", evo_atol(nptr));
    evo_logd(TestWrapperTag, "TestWrapper::test_string_number atoll %lld", evo_atoll(nptr));
    evo_logd(TestWrapperTag, "TestWrapper::test_string_number atof %f", evo_atof(nptr));
    evo_logd(TestWrapperTag, "TestWrapper::test_string_number str");
    evo_logd(TestWrapperTag, "TestWrapper::test_string_number strtod %f", evo_strtod(nptr, NULL));
    evo_logd(TestWrapperTag, "TestWrapper::test_string_number strtof %f", evo_strtof(nptr, NULL));
    evo_logd(TestWrapperTag, "TestWrapper::test_string_number strtold %llf", evo_strtold(nptr, NULL));
    const CHAR *nptr2 = "1234567890123456789012345678901234567890";
    evo_logd(TestWrapperTag, "TestWrapper::test_string_number strtod %f", evo_strtod(nptr2, NULL));
    evo_logd(TestWrapperTag, "TestWrapper::test_string_number strtof %f", evo_strtof(nptr2, NULL));
    evo_logd(TestWrapperTag, "TestWrapper::test_string_number strtold %llf", evo_strtold(nptr2, NULL));
    evo_logd(TestWrapperTag, "TestWrapper::test_string_number strtol %ld", evo_strtol(nptr, NULL, 8));
    evo_logd(TestWrapperTag, "TestWrapper::test_string_number strtol %ld", evo_strtol(nptr, NULL, 100));
    evo_logd(TestWrapperTag, "TestWrapper::test_string_number strtoll %lld", evo_strtoll(nptr, NULL, 16));
    evo_logd(TestWrapperTag, "TestWrapper::test_string_number strtoul %lu", evo_strtoul(nptr, NULL, 8));
    evo_logd(TestWrapperTag, "TestWrapper::test_string_number strtoul %lu", evo_strtoul(nptr, NULL, 100));
    evo_logd(TestWrapperTag, "TestWrapper::test_string_number strtoull %llu", evo_strtoull(nptr, NULL, 16));
}

VOID TestWrapper::test_mem()
{
    CHAR s[20] = { 0 };
    evo_logd(TestWrapperTag, "TestWrapper::test_mem %s %s", s, evo_memset(s, '1', sizeof(s) - 1));
    WCHAR ws[20];
    INT32 n;
    evo_logd(TestWrapperTag, "TestWrapper::test_mem %d", n = sizeof(WCHAR));
    for (INT32 i = 0; i < n; ++i) {
        ws[19 - i] = 0;
    }
    evo_logd(TestWrapperTag, "TestWrapper::test_mem %s %s", ws, evo_wmemset(ws, '2', sizeof(ws) / sizeof(WCHAR) - n));
    evo_bzero(s, sizeof(s));
    evo_logd(TestWrapperTag, "TestWrapper::test_mem %s", s);
    const CHAR *from = "1234";
    CHAR to[10] = { 0 };
    evo_swab(from, to, strlen(from));
    evo_logd(TestWrapperTag, "TestWrapper::test_mem %s %s", from, to);
}

VOID TestWrapper::test_fd()
{
    const CHAR *file = "testfd";
    MODE_T mode = S_IRWXU | S_IRWXG | S_IRWXO;
    INT32 fd = evo_create(file, O_CREAT | O_EXCL | O_RDWR, mode);
    evo_logd(TestWrapperTag, "TestWrapper::test_fd create=%d", fd);
    evo_logd(TestWrapperTag, "TestWrapper::test_fd close=%d", evo_close(fd));
    fd = evo_open(file, O_TRUNC | O_RDWR);
    evo_logd(TestWrapperTag, "TestWrapper::test_fd open=%d", fd);
    const CHAR *foo = "foobar";
    CHAR buf[10] = { 0 };
    evo_logd(TestWrapperTag, "TestWrapper::test_fd write=%ld", evo_write(fd, foo, strlen(foo)));
    evo_logd(TestWrapperTag, "TestWrapper::test_fd lseek=%lld", evo_lseek(fd, 0, SEEK_SET));
    evo_logd(TestWrapperTag, "TestWrapper::test_fd read=%s %ld", buf, evo_read(fd, buf, sizeof(buf) - 1));
    INT32 dupfd = evo_fcntl(fd, F_DUPFD);
    evo_logd(TestWrapperTag, "TestWrapper::test_fd F_DUPFD=%d", dupfd);
    evo_close(dupfd);
    dupfd = evo_fcntl_int(fd, F_DUPFD, 10);
    evo_logd(TestWrapperTag, "TestWrapper::test_fd F_DUPFD=%d", dupfd);
    evo_close(dupfd);
    struct flock lock;
    evo_fcntl_flock(fd, F_GETLK, &lock);
    evo_logd(TestWrapperTag, "TestWrapper::test_fd F_GETLK type=%d", lock.l_type);
    evo_logd(TestWrapperTag, "TestWrapper::test_fd close=%d", evo_close(fd));

    INT32 sfd[2] = { 0 };
    evo_socketpair(AF_LOCAL, SOCK_STREAM, 0, sfd);
    evo_logd(TestWrapperTag, "TestWrapper::test_fd socketpair=%d %d", sfd[0], sfd[1]);
    evo_logd(TestWrapperTag, "TestWrapper::test_fd socketpair write=%ld", evo_write(sfd[1], foo, strlen(foo)));

    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(sfd[0], &readfds);
    evo_logd(TestWrapperTag, "TestWrapper::test_fd socketpair select=%d", evo_select(sfd[0] + 1, &readfds, NULL, NULL, NULL));
    INT32 ret = FD_ISSET(sfd[0], &readfds);
    evo_logd(TestWrapperTag, "TestWrapper::test_fd socketpair select FD_ISSET=%d", ret);
    evo_memset(buf, 0, sizeof(buf));
    evo_logd(TestWrapperTag, "TestWrapper::test_fd socketpair read=%ld %s", evo_read(sfd[0], buf, sizeof(buf) - 1), buf);
    FD_CLR(sfd[0], &readfds);
    evo_close(sfd[0]);
    evo_close(sfd[1]);

    INT32 fds[2] = { 0 };
    evo_socketpair(AF_LOCAL, SOCK_STREAM, 0, fds);
    evo_logd(TestWrapperTag, "TestWrapper::test_fd socketpair-fork=%d %d", fds[0], fds[1]);
    PID_T pid = evo_fork();
    if (0 == pid) {
        evo_close(fds[0]);
        evo_write(fds[1], foo, strlen(foo));
        evo_close(fds[1]);
        evo_exit(0);
    }
    evo_close(fds[1]);
    evo_memset(buf, 0, sizeof(buf));
    evo_read(fds[0], buf, sizeof(buf) - 1);
    evo_close(fds[0]);
    evo_logd(TestWrapperTag, "TestWrapper::test_fd socketpair-fork read=%s", buf);
}

VOID TestWrapper::test_id()
{
    evo_logd(TestWrapperTag, "TestWrapper::test_id getpid=%d", evo_getpid());
    evo_logd(TestWrapperTag, "TestWrapper::test_id getppid=%d", evo_getppid());
    evo_logd(TestWrapperTag, "TestWrapper::test_id gettid=%d", evo_gettid());
    evo_logd(TestWrapperTag, "TestWrapper::test_id getuid=%u", evo_getuid());
    evo_logd(TestWrapperTag, "TestWrapper::test_id geteuid=%u", evo_geteuid());
    evo_logd(TestWrapperTag, "TestWrapper::test_id setuid=%d", evo_setuid(5000));
    evo_logd(TestWrapperTag, "TestWrapper::test_id seteuid=%d", evo_seteuid(5001));
    evo_logd(TestWrapperTag, "TestWrapper::test_id getgid=%u", evo_getgid());
    evo_logd(TestWrapperTag, "TestWrapper::test_id getegid=%u", evo_getegid());
    evo_logd(TestWrapperTag, "TestWrapper::test_id setgid=%d", evo_setgid(5002));
    evo_logd(TestWrapperTag, "TestWrapper::test_id setegid=%d", evo_setegid(5003));
    evo_logd(TestWrapperTag, "TestWrapper::test_id getpid=%d", evo_getpid());
    evo_logd(TestWrapperTag, "TestWrapper::test_id getpgid=%d", evo_getpgid(0));
    evo_logd(TestWrapperTag, "TestWrapper::test_id setpgid=%d", evo_setpgid(0, 0));
    evo_logd(TestWrapperTag, "TestWrapper::test_id getpgid=%d", evo_getpgid(0));
}

static VOID _Signal_hanlder(INT32 sig)
{
    evo_logd(TestWrapperTag, "_Signal_hanlder sig=%d", sig);
}

VOID TestWrapper::test_process()
{
    evo_logd(TestWrapperTag, "TestWrapper::test_process sleep=%u", evo_sleep(1));
    evo_logd(TestWrapperTag, "TestWrapper::test_process signal=%p", evo_signal(10, _Signal_hanlder));
    struct sigaction act;
    act.sa_handler = _Signal_hanlder;
    evo_logd(TestWrapperTag, "TestWrapper::test_process sigaction=%p", evo_sigaction(16, &act, NULL));
    evo_logd(TestWrapperTag, "TestWrapper::test_process kill=%d", evo_kill(getpid(), 10));
    evo_logd(TestWrapperTag, "TestWrapper::test_process raise=%d", evo_raise(16));
//    evo_exit(0); // exit
    PID_T pid = evo_fork();
    PID_T child = -1;
    if (0 == pid) {
        evo_logd(TestWrapperTag, "TestWrapper::test_process child");
        evo_logd(TestWrapperTag, "TestWrapper::test_process execl=%d", evo_execl("/bin/ls", "ls", "-l", "-a", EVOWRAPPER_PARAM_SENTINEL));
    }
    else {
        evo_logd(TestWrapperTag, "TestWrapper::test_process parent");
        child = pid;
    }
    evo_logd(TestWrapperTag, "TestWrapper::test_process waitpid=%d", evo_waitpid(child, NULL, 0));
}

#define TestWrapper_Posix_MQ "/TestWrapper"
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

// simple test
VOID TestWrapper::test_posix_mq()
{
    MQD_T mq = evo_mq_create(TestWrapper_Posix_MQ, O_CREAT | O_EXCL | O_WRONLY, FILE_MODE, NULL);
    evo_logd(TestWrapperTag, "TestWrapper::test_posix_mq create=%d %s", mq, TestWrapper_Posix_MQ);

    const CHAR *msg = "TestWrapper::test_posix_mq";
    INT32 ret = evo_mq_send(mq, msg, strlen(msg) + 1, 0);
    evo_logd(TestWrapperTag, "TestWrapper::test_posix_mq send=%d %s", ret, msg);

    ret = evo_mq_close(mq);
    evo_logd(TestWrapperTag, "TestWrapper::test_posix_mq close=%d %d", ret, mq);

    mq = evo_mq_open(TestWrapper_Posix_MQ, O_RDONLY);
    evo_logd(TestWrapperTag, "TestWrapper::test_posix_mq open=%d %s", mq, TestWrapper_Posix_MQ);

    struct mq_attr attr;
    ret = evo_mq_getattr(mq, &attr);
    evo_logd(TestWrapperTag, "TestWrapper::test_posix_mq getattr=%ld %ld %ld %ld", attr.mq_flags, attr.mq_curmsgs, attr.mq_maxmsg, attr.mq_msgsize);

    UINT32 prio;
    CHAR *buf = (CHAR*)calloc(attr.mq_msgsize + 1, sizeof(CHAR));
    SSIZE_T rcv = evo_mq_receive(mq, buf, attr.mq_msgsize, &prio);
    evo_logd(TestWrapperTag, "TestWrapper::test_posix_mq receive=%d %s %d", rcv, buf, prio);

    ret = evo_mq_close(mq);
    evo_logd(TestWrapperTag, "TestWrapper::test_posix_mq close=%d", ret);

    ret = evo_mq_unlink(TestWrapper_Posix_MQ);
    evo_logd(TestWrapperTag, "TestWrapper::test_posix_mq unlink=%d", ret);
}

static VOID* _Thread_routine(VOID *arg)
{
    evo_logd(TestWrapperTag, "_Thread_routine arg=%p", arg);
    evo_pthread_exit(NULL);
    return NULL;
}

static VOID* _Thread_routine2(VOID *arg)
{
    evo_sleep(1);
    evo_logd(TestWrapperTag, "_Thread_routine2 arg=%p", arg);
    evo_pthread_exit(NULL);
    return NULL;
}

static VOID* _Thread_routine3(VOID *arg)
{
    evo_logd(TestWrapperTag, "_Thread_routine3 arg=%p", arg);
    evo_pthread_detach(evo_pthread_self());
    evo_pthread_exit(NULL);
    return NULL;
}

VOID TestWrapper::test_pthread()
{
    TID_T tid = 0;
    evo_logd(TestWrapperTag, "TestWrapper::test_pthread tid=%lu create=%d", tid, evo_pthread_create(&tid, NULL, _Thread_routine, NULL));
    evo_logd(TestWrapperTag, "TestWrapper::test_pthread join=%d", evo_pthread_join(tid, NULL));
    TID_T tid2 = 0;
    evo_pthread_create(&tid2, NULL, _Thread_routine2, NULL);
    evo_logd(TestWrapperTag, "TestWrapper::test_pthread kill=%d", evo_pthread_kill(tid2, 0));
    evo_logd(TestWrapperTag, "TestWrapper::test_pthread cancel=%d", evo_pthread_cancel(tid2));
    evo_sleep(2);
    TID_T tid3 = 0;
    evo_pthread_create(&tid3, NULL, _Thread_routine3, NULL);
    evo_sleep(1);
    evo_logd(TestWrapperTag, "TestWrapper::test_pthread equal=%d", evo_pthread_equal(tid, tid2));
    evo_logd(TestWrapperTag, "TestWrapper::test_pthread getconcurrency=%d", evo_getconcurrency());
    evo_logd(TestWrapperTag, "TestWrapper::test_pthread setconcurrency=%d", evo_setconcurrency(10));
    evo_logd(TestWrapperTag, "TestWrapper::test_pthread getconcurrency=%d", evo_getconcurrency());
}

pthread_mutex_t _Mutex = PTHREAD_MUTEX_INITIALIZER;
static INT32 _Thread_mutex_count = 0;

static VOID* _Thread_mutex_routine(VOID *arg)
{
    EVO_UNUSED(arg);
    evo_pthread_mutex_lock(&_Mutex);
    for (INT32 i = 0; i < 10; ++i) {
        evo_logd(TestWrapperTag, "_Thread_mutex_routine %d", _Thread_mutex_count += *(INT32*)arg);
        usleep(1000);
    }
    evo_pthread_mutex_unlock(&_Mutex);
    return NULL;
}

// simple test
VOID TestWrapper::test_pthread_mutex()
{
    TID_T tid, tid2;
    INT32 increment[2] = {1, 100};
    evo_pthread_create(&tid, NULL, _Thread_mutex_routine, &increment[0]);
    evo_pthread_create(&tid2, NULL, _Thread_mutex_routine, &increment[1]);
    evo_pthread_join(tid, NULL);
    evo_pthread_join(tid2, NULL);
}

pthread_cond_t _Cond = PTHREAD_COND_INITIALIZER;
static INT32 _Thread_cond_count = 0;
const INT32 _Thread_cond_count_max = 10;

static VOID* _Thread_cond_read(VOID *arg)
{
    EVO_UNUSED(arg);
    evo_pthread_mutex_lock(&_Mutex);
    if (_Thread_cond_count_max > _Thread_cond_count) {
        evo_logd(TestWrapperTag, "_Thread_cond_read before %d", _Thread_cond_count);
        evo_pthread_cond_wait(&_Cond, &_Mutex);
        evo_logd(TestWrapperTag, "_Thread_cond_read after %d", _Thread_cond_count);
    }
    _Thread_cond_count = 0;
    evo_pthread_mutex_unlock(&_Mutex);
    return NULL;
}

static VOID* _Thread_cond_write(VOID *arg)
{
    EVO_UNUSED(arg);
    evo_pthread_mutex_lock(&_Mutex);
    while (_Thread_cond_count_max > _Thread_cond_count) {
        _Thread_cond_count++;
        evo_logd(TestWrapperTag, "_Thread_cond_write before %d", _Thread_cond_count);
        evo_pthread_cond_signal(&_Cond);
        evo_logd(TestWrapperTag, "_Thread_cond_write after %d", _Thread_cond_count);
    }
    evo_pthread_mutex_unlock(&_Mutex);
    return NULL;
}

// simple test
VOID TestWrapper::test_pthread_condition()
{
    TID_T tid, tid2;
    evo_pthread_create(&tid, NULL, _Thread_cond_read, NULL);
    usleep(1000 * 500);
    evo_pthread_create(&tid2, NULL, _Thread_cond_write, NULL);
    evo_pthread_join(tid, NULL);
    evo_pthread_join(tid2, NULL);
}

pthread_rwlock_t _Rwlock = PTHREAD_RWLOCK_INITIALIZER;
static INT32 _Thread_rwlock_count = 0;
const INT32 _Thread_rwlock_count_max = 10;

static VOID* _Thread_rwlock_read(VOID *arg)
{
    evo_pthread_rwlock_rdlock(&_Rwlock);
    for (INT32 i = 0; i < 10; ++i) {
        evo_logd(TestWrapperTag, "_Thread_rwlock_read %d %d %d", *(INT32*)arg, _Thread_rwlock_count, i);
        usleep(1000 * 100);
    }
    evo_pthread_rwlock_unlock(&_Rwlock);
    return NULL;
}

static VOID* _Thread_rwlock_write(VOID *arg)
{
    EVO_UNUSED(arg);
    evo_pthread_rwlock_wrlock(&_Rwlock);
    while (_Thread_rwlock_count_max > _Thread_rwlock_count) {
        _Thread_rwlock_count++;
        evo_logd(TestWrapperTag, "_Thread_rwlock_write %d", _Thread_rwlock_count);
        usleep(1000 * 100);
    }
    evo_pthread_rwlock_unlock(&_Rwlock);
    return NULL;
}

// simple test
VOID TestWrapper::test_pthread_rwlock()
{
    TID_T tid, tid2, tid3;
    INT32 read = 1, read2 = 100;
    evo_pthread_create(&tid, NULL, _Thread_rwlock_read, &read);
    evo_pthread_create(&tid2, NULL, _Thread_rwlock_read, &read2);
    evo_pthread_create(&tid3, NULL, _Thread_rwlock_write, NULL);
    evo_pthread_join(tid, NULL);
    evo_pthread_join(tid2, NULL);
    evo_pthread_join(tid3, NULL);
}

pthread_spinlock_t _Spinlock;
static INT32 _Thread_spinlock_count = 0;

static VOID* _Thread_spinlock_routine(VOID *arg)
{
    INT32 flag = *(INT32*)arg;
    evo_pthread_spin_lock(&_Spinlock);
    for (INT32 i = 0; i < 10; ++i) {
        _Thread_spinlock_count += flag;
        evo_logd(TestWrapperTag, "_Thread_spinlock_routine %d", _Thread_spinlock_count);
        usleep(1000);
    }
    evo_pthread_spin_unlock(&_Spinlock);
    return NULL;
}

// simple test
VOID TestWrapper::test_pthread_spinlock()
{
    TID_T tid, tid2;
    INT32 read = 1, read2 = 100;
    evo_pthread_spin_init(&_Spinlock, 0);
    evo_pthread_create(&tid, NULL, _Thread_spinlock_routine, &read);
    evo_pthread_create(&tid2, NULL, _Thread_spinlock_routine, &read2);
    evo_pthread_join(tid, NULL);
    evo_pthread_join(tid2, NULL);
    evo_pthread_spin_destroy(&_Spinlock);
}

static pthread_barrier_t _Barrier;
const INT32 _Thread_barrier_thread = 5;

static VOID* _Thread_barrier_routine(VOID *arg)
{
    INT32 flag = *(INT32*)arg;
    evo_pthread_barrier_wait(&_Barrier);
    evo_logd(TestWrapperTag, "_Thread_barrier_routine %d", flag);
    return NULL;
}

// simple test
VOID TestWrapper::test_pthread_barrier()
{
    TID_T threads[_Thread_barrier_thread];
    INT32 flags[_Thread_barrier_thread];
    for (INT32 i = 0; i < _Thread_barrier_thread; ++i) {
        flags[i] = i;
    }
    evo_pthread_barrier_init(&_Barrier, NULL, _Thread_barrier_thread);
    for (INT32 i = 0; i < _Thread_barrier_thread - 1; ++i) {
        evo_pthread_create(&threads[i], NULL, _Thread_barrier_routine, &flags[i]);
    }
    evo_sleep(1);
    evo_pthread_create(&threads[_Thread_barrier_thread - 1], NULL, _Thread_barrier_routine, &flags[_Thread_barrier_thread - 1]);
    for (INT32 i = 0; i < _Thread_barrier_thread; ++i) {
        evo_pthread_join(threads[i], NULL);
    }
    evo_pthread_barrier_destroy(&_Barrier);
}

VOID TestWrapper::test_dl()
{
    const CHAR *lib = "./../lib/libtestdl.so";
    VOID *handle = evo_dlopen(lib, RTLD_NOW);
    ASSERT(NULL != handle);
    const CHAR *symble = "test_abs";
    typedef INT32(*symble_func)(INT32);
    symble_func func = (symble_func)evo_dlsym(handle, symble);
    ASSERT(NULL != func);
    INT32 value = -100;
    INT32 ret = func(value);
    evo_logd(TestWrapperTag, "TestWrapper::test_dl value>ret %d>%d", value, ret);
    ASSERT(evo_dlclose(handle) == 0);
    Dl_info info;
    // TODO dladdr
    ret = evo_dladdr((VOID*)func, &info);
    evo_logd(TestWrapperTag, "TestWrapper::test_dl dlinfo %d", ret);
    if (ret > 0) {
        evo_logd(TestWrapperTag, "TestWrapper::test_dl dlinfo %p %s %p %s", info.dli_fbase, info.dli_fname, info.dli_saddr, info.dli_sname);
    }
}

EVO_TEST_RUN(TestWrapper)
