/**
 * @file Wrapper.h
 * @brief Wraps some functions
 */

#ifndef EVO_EVOWRAPPER_H
#define EVO_EVOWRAPPER_H

#include "Global.h"

#include <signal.h>
#include <sys/select.h>

EVO_BEGIN_DECLS

/*
file: /usr/include/x86_64-linux-gnu/asm/unistd_64.h
define: _ASM_X86_UNISTD_64_H
#define __NR_read 0
#define __NR_write 1
#define __NR_open 2
#define __NR_close 3
#define __NR_stat 4
#define __NR_fstat 5
#define __NR_lstat 6
#define __NR_poll 7
#define __NR_lseek 8
#define __NR_mmap 9
#define __NR_mprotect 10
#define __NR_munmap 11
#define __NR_brk 12
#define __NR_rt_sigaction 13
#define __NR_rt_sigprocmask 14
#define __NR_rt_sigreturn 15
#define __NR_ioctl 16
#define __NR_pread64 17
#define __NR_pwrite64 18
#define __NR_readv 19
#define __NR_writev 20
#define __NR_access 21
#define __NR_pipe 22
#define __NR_select 23
#define __NR_sched_yield 24
#define __NR_mremap 25
#define __NR_msync 26
#define __NR_mincore 27
#define __NR_madvise 28
#define __NR_shmget 29
#define __NR_shmat 30
#define __NR_shmctl 31
#define __NR_dup 32
#define __NR_dup2 33
#define __NR_pause 34
#define __NR_nanosleep 35
#define __NR_getitimer 36
#define __NR_alarm 37
#define __NR_setitimer 38
#define __NR_getpid 39
#define __NR_sendfile 40
#define __NR_socket 41
#define __NR_connect 42
#define __NR_accept 43
#define __NR_sendto 44
#define __NR_recvfrom 45
#define __NR_sendmsg 46
#define __NR_recvmsg 47
#define __NR_shutdown 48
#define __NR_bind 49
#define __NR_listen 50
#define __NR_getsockname 51
#define __NR_getpeername 52
#define __NR_socketpair 53
#define __NR_setsockopt 54
#define __NR_getsockopt 55
#define __NR_clone 56
#define __NR_fork 57
#define __NR_vfork 58
#define __NR_execve 59
#define __NR_exit 60
#define __NR_wait4 61
#define __NR_kill 62
#define __NR_uname 63
#define __NR_semget 64
#define __NR_semop 65
#define __NR_semctl 66
#define __NR_shmdt 67
#define __NR_msgget 68
#define __NR_msgsnd 69
#define __NR_msgrcv 70
#define __NR_msgctl 71
#define __NR_fcntl 72
#define __NR_flock 73
#define __NR_fsync 74
#define __NR_fdatasync 75
#define __NR_truncate 76
#define __NR_ftruncate 77
#define __NR_getdents 78
#define __NR_getcwd 79
#define __NR_chdir 80
#define __NR_fchdir 81
#define __NR_rename 82
#define __NR_mkdir 83
#define __NR_rmdir 84
#define __NR_creat 85
#define __NR_link 86
#define __NR_unlink 87
#define __NR_symlink 88
#define __NR_readlink 89
#define __NR_chmod 90
#define __NR_fchmod 91
#define __NR_chown 92
#define __NR_fchown 93
#define __NR_lchown 94
#define __NR_umask 95
#define __NR_gettimeofday 96
#define __NR_getrlimit 97
#define __NR_getrusage 98
#define __NR_sysinfo 99
#define __NR_times 100
#define __NR_ptrace 101
#define __NR_getuid 102
#define __NR_syslog 103
#define __NR_getgid 104
#define __NR_setuid 105
#define __NR_setgid 106
#define __NR_geteuid 107
#define __NR_getegid 108
#define __NR_setpgid 109
#define __NR_getppid 110
#define __NR_getpgrp 111
#define __NR_setsid 112
#define __NR_setreuid 113
#define __NR_setregid 114
#define __NR_getgroups 115
#define __NR_setgroups 116
#define __NR_setresuid 117
#define __NR_getresuid 118
#define __NR_setresgid 119
#define __NR_getresgid 120
#define __NR_getpgid 121
#define __NR_setfsuid 122
#define __NR_setfsgid 123
#define __NR_getsid 124
#define __NR_capget 125
#define __NR_capset 126
#define __NR_rt_sigpending 127
#define __NR_rt_sigtimedwait 128
#define __NR_rt_sigqueueinfo 129
#define __NR_rt_sigsuspend 130
#define __NR_sigaltstack 131
#define __NR_utime 132
#define __NR_mknod 133
#define __NR_uselib 134
#define __NR_personality 135
#define __NR_ustat 136
#define __NR_statfs 137
#define __NR_fstatfs 138
#define __NR_sysfs 139
#define __NR_getpriority 140
#define __NR_setpriority 141
#define __NR_sched_setparam 142
#define __NR_sched_getparam 143
#define __NR_sched_setscheduler 144
#define __NR_sched_getscheduler 145
#define __NR_sched_get_priority_max 146
#define __NR_sched_get_priority_min 147
#define __NR_sched_rr_get_interval 148
#define __NR_mlock 149
#define __NR_munlock 150
#define __NR_mlockall 151
#define __NR_munlockall 152
#define __NR_vhangup 153
#define __NR_modify_ldt 154
#define __NR_pivot_root 155
#define __NR__sysctl 156
#define __NR_prctl 157
#define __NR_arch_prctl 158
#define __NR_adjtimex 159
#define __NR_setrlimit 160
#define __NR_chroot 161
#define __NR_sync 162
#define __NR_acct 163
#define __NR_settimeofday 164
#define __NR_mount 165
#define __NR_umount2 166
#define __NR_swapon 167
#define __NR_swapoff 168
#define __NR_reboot 169
#define __NR_sethostname 170
#define __NR_setdomainname 171
#define __NR_iopl 172
#define __NR_ioperm 173
#define __NR_create_module 174
#define __NR_init_module 175
#define __NR_delete_module 176
#define __NR_get_kernel_syms 177
#define __NR_query_module 178
#define __NR_quotactl 179
#define __NR_nfsservctl 180
#define __NR_getpmsg 181
#define __NR_putpmsg 182
#define __NR_afs_syscall 183
#define __NR_tuxcall 184
#define __NR_security 185
#define __NR_gettid 186
#define __NR_readahead 187
#define __NR_setxattr 188
#define __NR_lsetxattr 189
#define __NR_fsetxattr 190
#define __NR_getxattr 191
#define __NR_lgetxattr 192
#define __NR_fgetxattr 193
#define __NR_listxattr 194
#define __NR_llistxattr 195
#define __NR_flistxattr 196
#define __NR_removexattr 197
#define __NR_lremovexattr 198
#define __NR_fremovexattr 199
#define __NR_tkill 200
#define __NR_time 201
#define __NR_futex 202
#define __NR_sched_setaffinity 203
#define __NR_sched_getaffinity 204
#define __NR_set_thread_area 205
#define __NR_io_setup 206
#define __NR_io_destroy 207
#define __NR_io_getevents 208
#define __NR_io_submit 209
#define __NR_io_cancel 210
#define __NR_get_thread_area 211
#define __NR_lookup_dcookie 212
#define __NR_epoll_create 213
#define __NR_epoll_ctl_old 214
#define __NR_epoll_wait_old 215
#define __NR_remap_file_pages 216
#define __NR_getdents64 217
#define __NR_set_tid_address 218
#define __NR_restart_syscall 219
#define __NR_semtimedop 220
#define __NR_fadvise64 221
#define __NR_timer_create 222
#define __NR_timer_settime 223
#define __NR_timer_gettime 224
#define __NR_timer_getoverrun 225
#define __NR_timer_delete 226
#define __NR_clock_settime 227
#define __NR_clock_gettime 228
#define __NR_clock_getres 229
#define __NR_clock_nanosleep 230
#define __NR_exit_group 231
#define __NR_epoll_wait 232
#define __NR_epoll_ctl 233
#define __NR_tgkill 234
#define __NR_utimes 235
#define __NR_vserver 236
#define __NR_mbind 237
#define __NR_set_mempolicy 238
#define __NR_get_mempolicy 239
#define __NR_mq_open 240
#define __NR_mq_unlink 241
#define __NR_mq_timedsend 242
#define __NR_mq_timedreceive 243
#define __NR_mq_notify 244
#define __NR_mq_getsetattr 245
#define __NR_kexec_load 246
#define __NR_waitid 247
#define __NR_add_key 248
#define __NR_request_key 249
#define __NR_keyctl 250
#define __NR_ioprio_set 251
#define __NR_ioprio_get 252
#define __NR_inotify_init 253
#define __NR_inotify_add_watch 254
#define __NR_inotify_rm_watch 255
#define __NR_migrate_pages 256
#define __NR_openat 257
#define __NR_mkdirat 258
#define __NR_mknodat 259
#define __NR_fchownat 260
#define __NR_futimesat 261
#define __NR_newfstatat 262
#define __NR_unlinkat 263
#define __NR_renameat 264
#define __NR_linkat 265
#define __NR_symlinkat 266
#define __NR_readlinkat 267
#define __NR_fchmodat 268
#define __NR_faccessat 269
#define __NR_pselect6 270
#define __NR_ppoll 271
#define __NR_unshare 272
#define __NR_set_robust_list 273
#define __NR_get_robust_list 274
#define __NR_splice 275
#define __NR_tee 276
#define __NR_sync_file_range 277
#define __NR_vmsplice 278
#define __NR_move_pages 279
#define __NR_utimensat 280
#define __NR_epoll_pwait 281
#define __NR_signalfd 282
#define __NR_timerfd_create 283
#define __NR_eventfd 284
#define __NR_fallocate 285
#define __NR_timerfd_settime 286
#define __NR_timerfd_gettime 287
#define __NR_accept4 288
#define __NR_signalfd4 289
#define __NR_eventfd2 290
#define __NR_epoll_create1 291
#define __NR_dup3 292
#define __NR_pipe2 293
#define __NR_inotify_init1 294
#define __NR_preadv 295
#define __NR_pwritev 296
#define __NR_rt_tgsigqueueinfo 297
#define __NR_perf_event_open 298
#define __NR_recvmmsg 299
#define __NR_fanotify_init 300
#define __NR_fanotify_mark 301
#define __NR_prlimit64 302
#define __NR_name_to_handle_at 303
#define __NR_open_by_handle_at 304
#define __NR_clock_adjtime 305
#define __NR_syncfs 306
#define __NR_sendmmsg 307
#define __NR_setns 308
#define __NR_getcpu 309
#define __NR_process_vm_readv 310
#define __NR_process_vm_writev 311
#define __NR_kcmp 312
#define __NR_finit_module 313
#define __NR_sched_setattr 314
#define __NR_sched_getattr 315
#define __NR_renameat2 316
#define __NR_seccomp 317
*/

// param
#define EVOWRAPPER_PARAM_SENTINEL "EVO"
#define EVOWRAPPER_PARAM_MAX 4
#define EVOWRAPPER_PARAM_LEN 16
#define EVOWRAPPER_PARAM_BUFSIZ (EVOWRAPPER_PARAM_MAX * EVOWRAPPER_PARAM_LEN)

// env
#define EVOWRAPPER_GETENV "getenv"
#define EVOWRAPPER_SECURE_GETENV "secure_getenv"
#define EVOWRAPPER_PUTENV "putenv"
#define EVOWRAPPER_SETENV "setenv"
#define EVOWRAPPER_UNSETENV "unsetenv"
#define EVOWRAPPER_CLEARENV "clearenv"
#define EVOWRAPPER_GETAUXVAL "getauxval"

EVO_APICALL CHAR* evo_getenv(const CHAR *name);
EVO_APICALL CHAR* evo_secure_getenv(const CHAR *name);
EVO_APICALL INT32 evo_putenv(CHAR *string);
EVO_APICALL INT32 evo_setenv(const CHAR *name, const CHAR *value, INT32 overwrite);
EVO_APICALL INT32 evo_unsetenv(const CHAR *string);
EVO_APICALL INT32 evo_clearenv();
EVO_APICALL UINT64 evo_getauxval(UINT64 type);

// string
#define EVOWRAPPER_STPCPY "stpcpy"
#define EVOWRAPPER_STRCAT "strcat"
#define EVOWRAPPER_STRNCAT "strncat"
#define EVOWRAPPER_STRCHR "strchr"
#define EVOWRAPPER_STRRCHR "strrchr"
#define EVOWRAPPER_STRCHRNUL "strchrnul"
#define EVOWRAPPER_STRCMP "strcmp"
#define EVOWRAPPER_STRNCMP "strncmp"
#define EVOWRAPPER_STRCOLL "strcoll"
#define EVOWRAPPER_STRCPY "strcpy"
#define EVOWRAPPER_STRNCPY "strncpy"
#define EVOWRAPPER_STRSPN "strspn"
#define EVOWRAPPER_STRCSPN "strcspn"
#define EVOWRAPPER_STRDUP "strdup"
#define EVOWRAPPER_STRNDUP "strndup"
#define EVOWRAPPER_STRDUPA "strdupa"
#define EVOWRAPPER_STRNDUPA "strndupa"
#define EVOWRAPPER_STRFRY "strfry"
#define EVOWRAPPER_STRLEN "strlen"
#define EVOWRAPPER_STRNLEN "strnlen"
#define EVOWRAPPER_WCSLEN "wcslen"
#define EVOWRAPPER_WCSNLEN "wcsnlen"
#define EVOWRAPPER_STRPBRK "strpbrk"
#define EVOWRAPPER_STRSEP "strsep"
#define EVOWRAPPER_STRSTR "strstr"
#define EVOWRAPPER_STRCASESTR "strcasestr"
#define EVOWRAPPER_STRTOK "strtok"
#define EVOWRAPPER_STRTOK_R "strtok_r"
#define EVOWRAPPER_STRXFRM "strxfrm"
#define EVOWRAPPER_STRCASECMP "strcasecmp"
#define EVOWRAPPER_STRNCASECMP "strncasecmp"
#define EVOWRAPPER_INDEX "index"
#define EVOWRAPPER_RINDEX "rindex"

EVO_APICALL CHAR* evo_stpcpy(CHAR *dest, const CHAR *src);
EVO_APICALL CHAR* evo_strcat(CHAR *dest, const CHAR *src);
EVO_APICALL CHAR* evo_strncat(CHAR *dest, const CHAR *src, SIZE_T n);
EVO_APICALL CHAR* evo_strchr(const CHAR *s, INT32 c);
EVO_APICALL CHAR* evo_strrchr(const CHAR *s, INT32 c);
EVO_APICALL CHAR* evo_strchrnul(const CHAR *s, INT32 c);
EVO_APICALL INT32 evo_strcmp(const CHAR *s1, const CHAR *s2);
EVO_APICALL INT32 evo_strncmp(const CHAR *s1, const CHAR *s2, SIZE_T n);
EVO_APICALL INT32 evo_strcoll(const CHAR *s1, const CHAR *s2);
EVO_APICALL CHAR* evo_strcpy(CHAR *dest, const CHAR *src);
EVO_APICALL CHAR* evo_strncpy(CHAR *dest, const CHAR *src, SIZE_T n);
EVO_APICALL SIZE_T evo_strspn(const CHAR *s, const CHAR *accept);
EVO_APICALL SIZE_T evo_strcspn(const CHAR *s, const CHAR *reject);
EVO_APICALL CHAR* evo_strdup(const CHAR *s);
EVO_APICALL CHAR* evo_strndup(const CHAR *s, SIZE_T n);
EVO_APICALL CHAR* evo_strdupa(const CHAR *s);
EVO_APICALL CHAR* evo_strndupa(const CHAR *s, SIZE_T n);
EVO_APICALL CHAR* evo_strfry(CHAR *string);
EVO_APICALL SIZE_T evo_strlen(const CHAR *s);
EVO_APICALL SIZE_T evo_strnlen(const CHAR *s, SIZE_T maxlen);
EVO_APICALL SIZE_T evo_wcslen(const WCHAR *s);
EVO_APICALL SIZE_T evo_wcsnlen(const WCHAR *s, SIZE_T maxlen);
EVO_APICALL CHAR* evo_strpbrk(const CHAR *s, const CHAR *accept);
EVO_APICALL CHAR* evo_strsep(CHAR **stringp, const CHAR *delim);
EVO_APICALL CHAR* evo_strstr(const CHAR *haystack, const CHAR *needle);
EVO_APICALL CHAR* evo_strcasestr(const CHAR *haystack, const CHAR *needle);
EVO_APICALL CHAR* evo_strtok(CHAR *s, const CHAR *delim);
EVO_APICALL CHAR* evo_strtok_r(CHAR *s, const CHAR *delim, CHAR **saveptr);
EVO_APICALL SIZE_T evo_strxfrm(CHAR *dest, const CHAR *src, SIZE_T n);
EVO_APICALL INT32 evo_strcasecmp(const CHAR *s1, const CHAR *s2);
EVO_APICALL INT32 evo_strncasecmp(const CHAR *s1, const CHAR *s2, SIZE_T n);
EVO_APICALL CHAR* evo_index(const CHAR *s, INT32 c);
EVO_APICALL CHAR* evo_rindex(const CHAR *s, INT32 c);

// string-number
#define EVOWRAPPER_ATOI "atoi"
#define EVOWRAPPER_ATOL "atol"
#define EVOWRAPPER_ATOLL "atoll"
#define EVOWRAPPER_ATOF "atof"
#define EVOWRAPPER_STRTOD "strtod"
#define EVOWRAPPER_STRTOF "strtof"
#define EVOWRAPPER_STRTOLD "strtold"
#define EVOWRAPPER_STRTOL "strtol"
#define EVOWRAPPER_STRTOLL "strtoll"
#define EVOWRAPPER_STRTOUL "strtoul"
#define EVOWRAPPER_STRTOULL "strtoull"

EVO_APICALL INT32 evo_atoi(const CHAR *nptr);
EVO_APICALL LONG evo_atol(const CHAR *nptr);
EVO_APICALL LLONG evo_atoll(const CHAR *nptr);
EVO_APICALL DOUBLE evo_atof(const CHAR *nptr);
EVO_APICALL DOUBLE evo_strtod(const CHAR *nptr, CHAR **endptr);
EVO_APICALL FLOAT evo_strtof(const CHAR *nptr, CHAR **endptr);
EVO_APICALL LDOUBLE evo_strtold(const CHAR *nptr, CHAR **endptr);
EVO_APICALL LONG evo_strtol(const CHAR *nptr, CHAR **endptr, INT32 base);
EVO_APICALL LLONG evo_strtoll(const CHAR *nptr, CHAR **endptr, INT32 base);
EVO_APICALL ULONG evo_strtoul(const CHAR *nptr, CHAR **endptr, INT32 base);
EVO_APICALL ULLONG evo_strtoull(const CHAR *nptr, CHAR **endptr, INT32 base);

// mem
#define EVOWRAPPER_MEMSET "memset"
#define EVOWRAPPER_WMEMSET "wmemset"
#define EVOWRAPPER_BZERO "bzero"
#define EVOWRAPPER_SWAB "swab"

EVO_APICALL VOID* evo_memset(VOID *s, INT32 c, SIZE_T n);
EVO_APICALL WCHAR* evo_wmemset(WCHAR *wcs, WCHAR wc, SIZE_T n);
EVO_APICALL VOID evo_bzero(VOID *s, SIZE_T n);
EVO_APICALL VOID evo_swab(const VOID *from, VOID *to, SSIZE_T n);

// fd
#define EVOWRAPPER_OPEN "open"
#define EVOWRAPPER_CREATE "create"
#define EVOWRAPPER_LSEEK "lseek"
#define EVOWRAPPER_WRITE "write"
#define EVOWRAPPER_READ "read"
#define EVOWRAPPER_CLOSE "close"
#define EVOWRAPPER_SAFE_WRITE "safe_write" // OK
#define EVOWRAPPER_SAFE_READ "safe_read" // NG
#define EVOWRAPPER_FCNTL "fcntl"
#define EVOWRAPPER_FCNTL_INT "fcntl_int"
#define EVOWRAPPER_FCNTL_FLOCK "fcntl_flock"
#define EVOWRAPPER_SOCKETPAIR "socketpair"
#define EVOWRAPPER_SELECT "select" // pselect

struct flock;
struct timeval;

EVO_APICALL INT32 evo_open(const CHAR *pathname, INT32 flags);
EVO_APICALL INT32 evo_create(const CHAR *pathname, INT32 flags, MODE_T mode);
EVO_APICALL OFF_T evo_lseek(INT32 fd, OFF_T offset, INT32 whence);
EVO_APICALL SSIZE_T evo_write(INT32 fd, const VOID *buf, SIZE_T count);
EVO_APICALL SSIZE_T evo_read(INT32 fd, VOID *buf, SIZE_T count);
EVO_APICALL INT32 evo_close(INT32 fd);
EVO_APICALL INT32 evo_safe_write(INT32 fd, const CHAR *buf, INT32 count);
EVO_APICALL INT32 evo_safe_read(INT32 fd, CHAR *buf, INT32 count);
EVO_APICALL INT32 evo_fcntl(INT32 fd, INT32 cmd);
EVO_APICALL INT32 evo_fcntl_int(INT32 fd, INT32 cmd, INT32 arg);
EVO_APICALL INT32 evo_fcntl_flock(INT32 fd, INT32 cmd, struct flock *arg);
EVO_APICALL INT32 evo_socketpair(INT32 domain, INT32 type, INT32 protocol, INT32 sv[2]);
EVO_APICALL INT32 evo_select(INT32 nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout); // pselect poll ppoll

#define EVO_SAFE_WRITE evo_safe_write
#define EVO_SAFE_READ evo_safe_read

// id
#define EVOWRAPPER_GETPID "getpid"
#define EVOWRAPPER_GETPPID "getppid"
#define EVOWRAPPER_GETTID 186
#define EVOWRAPPER_SYSCALL "syscall"
#define EVOWRAPPER_GETUID "getuid"
#define EVOWRAPPER_GETEUID "geteuid"
#define EVOWRAPPER_SETUID "setuid"
#define EVOWRAPPER_SETEUID "seteuid"
#define EVOWRAPPER_GETGID "getgid"
#define EVOWRAPPER_GETEGID "getegid"
#define EVOWRAPPER_SETGID "setgid"
#define EVOWRAPPER_SETEGID "setegid"
#define EVOWRAPPER_GETPGID "getpgid"
#define EVOWRAPPER_SETPGID "setpgid"

EVO_APICALL PID_T evo_getpid();
EVO_APICALL PID_T evo_getppid();
EVO_APICALL PID_T evo_gettid();
EVO_APICALL UID_T evo_getuid();
EVO_APICALL UID_T evo_geteuid();
EVO_APICALL INT32 evo_setuid(UID_T uid);
EVO_APICALL INT32 evo_seteuid(UID_T euid);
EVO_APICALL GID_T evo_getgid();
EVO_APICALL GID_T evo_getegid();
EVO_APICALL INT32 evo_setgid(GID_T gid);
EVO_APICALL INT32 evo_setegid(GID_T egid);
EVO_APICALL PID_T evo_getpgid(PID_T pid);
EVO_APICALL INT32 evo_setpgid(PID_T pid, PID_T pgid);

// process
#define EVOWRAPPER_SLEEP "sleep" // usleep nanosleep pause alarm ualarm
#define EVOWARPPER_SIGNAL "signal"
#define EVOWRAPPER_SIGACTION "sigaction"
#define EVOWRAPPER_KILL "kill"
#define EVOWRAPPER_RAISE "raise"
#define EVOWRAPPER_EXIT "exit" // _exit _Exit
#define EVOWRAPPER_FORK "fork" // vfork clone
#define EVOWRAPPER_WAITPID "waitpid" // wait waitid
#define EVOWRAPPER_EXECL "execl" // execlp execle execv execvp execvpe

struct sigaction;

typedef VOID (*SigHandler)(INT32 sig);

EVO_APICALL UINT32 evo_sleep(UINT32 seconds);
EVO_APICALL SigHandler evo_signal(INT32 signum, SigHandler handler);
EVO_APICALL INT32 evo_sigaction(INT32 sig, const struct sigaction *act, struct sigaction *oact);
EVO_APICALL INT32 evo_kill(PID_T pid, INT32 sig);
EVO_APICALL INT32 evo_raise(INT32 sig);
EVO_APICALL VOID evo_exit(INT32 status);
EVO_APICALL PID_T evo_fork();
EVO_APICALL PID_T evo_waitpid(PID_T pid, INT32 *status, INT32 options);
EVO_APICALL INT32 evo_execl(const CHAR *path, const CHAR *arg, ...);

// POSIX message queue
#define EVOWRAPPER_POSIX_MQ_OPEN "mq_open"
#define EVOWRAPPER_POSIX_MQ_CREATE "mq_create"
#define EVOWRAPPER_POSIX_MQ_CLOSE "mq_close"
#define EVOWRAPPER_POSIX_MQ_UNLINK "mq_unlink"
#define EVOWRAPPER_POSIX_MQ_GETATTR "mq_getattr"
#define EVOWRAPPER_POSIX_MQ_SETATTR "mq_setattr"
#define EVOWRAPPER_POSIX_MQ_SEND "mq_send" // mq_timedsend
#define EVOWRAPPER_POSIX_MQ_RECEIVE "mq_receive" // mq_timedreceive
#define EVOWRAPPER_POSIX_MQ_NOTIFY "mq_notify"

struct mq_attr;
struct sigevent;

EVO_APICALL MQD_T evo_mq_open(const CHAR *name, INT32 oflag);
EVO_APICALL MQD_T evo_mq_create(const CHAR *name, INT32 oflag, MODE_T mode, struct mq_attr *attr);
EVO_APICALL INT32 evo_mq_close(MQD_T mqdes);
EVO_APICALL INT32 evo_mq_unlink(const CHAR *name);
EVO_APICALL INT32 evo_mq_getattr(MQD_T mqdes, struct mq_attr *attr);
EVO_APICALL INT32 evo_mq_setattr(MQD_T mqdes, const struct mq_attr *newattr, struct mq_attr *oldattr);
EVO_APICALL INT32 evo_mq_send(MQD_T mqdes, const CHAR *msg_ptr, SIZE_T msg_len, UINT32 msg_prio);
EVO_APICALL SSIZE_T evo_mq_receive(MQD_T mqdes, CHAR *msg_ptr, SIZE_T msg_len, UINT32 *msg_prio);
EVO_APICALL INT32 evo_mq_notify(MQD_T mqdes, const struct sigevent *sevp);

// pthread
#define EVOWRAPPER_PTHREAD_CREATE "pthread_create"
#define EVOWRAPPER_PTHREAD_EXIT "pthread_exit"
#define EVOWRAPPER_PTHREAD_JOIN "pthread_join"
#define EVOWRAPPER_PTHREAD_CANCEL "pthread_cancel"
#define EVOWRAPPER_PTHREAD_DETACH "pthread_detach"
#define EVOWRAPPER_PTHREAD_SELF "pthread_self"
#define EVOWRAPPER_PTHREAD_KILL "pthread_kill"
#define EVOWRAPPER_PTHREAD_QEUAL "pthread_equal"
#define EVOWRAPPER_PTHREAD_GETCONCURRENCY "pthread_getconcurrency"
#define EVOWRAPPER_PTHREAD_SETCONCURRENCY "pthread_setconcurrency"

typedef VOID*(*thread_routine)(VOID*);

EVO_APICALL INT32 evo_pthread_create(TID_T *thread, const pthread_attr_t *attr, thread_routine p, VOID *arg);
EVO_APICALL VOID evo_pthread_exit(VOID *value_ptr);
EVO_APICALL INT32 evo_pthread_join(TID_T thread, VOID **retval);
EVO_APICALL INT32 evo_pthread_cancel(TID_T thread);
EVO_APICALL INT32 evo_pthread_detach(TID_T thread);
EVO_APICALL TID_T evo_pthread_self();
EVO_APICALL INT32 evo_pthread_kill(TID_T thread, INT32 sig);
EVO_APICALL INT32 evo_pthread_equal(TID_T t1, TID_T t2);
EVO_APICALL INT32 evo_getconcurrency();
EVO_APICALL INT32 evo_setconcurrency(INT32 new_level);

// pthread-mutex
#define EVOWRAPPER_PTHREAD_MUTEX_INIT "pthread_mutex_init"
#define EVOWRAPPER_PTHREAD_MUTEX_DESTROY "pthread_mutex_destroy"
#define EVOWRAPPER_PTHREAD_MUTEX_TRYLOCK "pthread_mutex_trylock"
#define EVOWRAPPER_PTHREAD_MUTEX_LOCK "pthread_mutex_lock"
#define EVOWRAPPER_PTHREAD_MUTEX_TIMEDLOCK "pthread_mutex_timedlock"
#define EVOWRAPPER_PTHREAD_MUTEX_UNLOCK "pthread_mutex_unlock"
#define EVOWRAPPER_PTHREAD_MUTEXATTR_INIT "pthread_mutexattr_init"
#define EVOWRAPPER_PTHREAD_MUTEXATTR_DESTROY "pthread_mutexattr_destroy"
#define EVOWRAPPER_PTHREAD_MUTEXATTR_SETPSHARED "pthread_mutexattr_setpshared"

struct timespec;

EVO_APICALL INT32 evo_pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
EVO_APICALL INT32 evo_pthread_mutex_destroy(pthread_mutex_t *mutex);
EVO_APICALL INT32 evo_pthread_mutex_trylock(pthread_mutex_t *mutex);
EVO_APICALL INT32 evo_pthread_mutex_lock(pthread_mutex_t *mutex);
EVO_APICALL INT32 evo_pthread_mutex_timedlock(pthread_mutex_t *mutex, const struct timespec *abstime);
EVO_APICALL INT32 evo_pthread_mutex_unlock(pthread_mutex_t *mutex);
EVO_APICALL INT32 evo_pthread_mutexattr_init(pthread_mutexattr_t *attr);
EVO_APICALL INT32 evo_pthread_mutexattr_destroy(pthread_mutexattr_t *attr);
EVO_APICALL INT32 evo_pthread_mutexattr_setpshared(pthread_mutexattr_t *attr, INT32 pshared);

// pthread-condition
#define EVOWRAPPER_PTHREAD_COND_INIT "pthread_cond_init"
#define EVOWRAPPER_PTHREAD_COND_DESTROY "pthread_cond_destroy"
#define EVOWRAPPER_PTHREAD_COND_SIGNAL "pthread_cond_signal"
#define EVOWRAPPER_PTHREAD_COND_BROADCAST "pthread_cond_broadcast"
#define EVOWRAPPER_PTHREAD_COND_WAIT "pthread_cond_wait"
#define EVOWRAPPER_PTHREAD_COND_TIMEDWAIT "pthread_cond_timedwait"
#define EVOWRAPPER_PTHREAD_CONDATTR_INIT "pthread_condattr_init"
#define EVOWRAPPER_PTHREAD_CONDATTR_DESTROY "pthread_condattr_destroy"
#define EVOWRAPPER_PTHREAD_CONDATTR_SETPSHARED "pthread_condattr_setpshared"

EVO_APICALL INT32 evo_pthread_cond_init(pthread_cond_t *cond, const pthread_condattr_t *cond_attr);
EVO_APICALL INT32 evo_pthread_cond_destroy(pthread_cond_t *cond);
EVO_APICALL INT32 evo_pthread_cond_signal(pthread_cond_t *cond);
EVO_APICALL INT32 evo_pthread_cond_broadcast(pthread_cond_t *cond);
EVO_APICALL INT32 evo_pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
EVO_APICALL INT32 evo_pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex, const struct timespec *abstime);
EVO_APICALL INT32 evo_pthread_condattr_init(pthread_condattr_t *attr);
EVO_APICALL INT32 evo_pthread_condattr_destroy(pthread_condattr_t *attr);
EVO_APICALL INT32 evo_pthread_condattr_setpshared(pthread_condattr_t *attr, INT32 pshared);

// pthread-rwlock
#define EVOWRAPPER_PTHREAD_RWLOCK_INIT "pthread_rwlock_init"
#define EVOWRAPPER_PTHREAD_RWLOCK_DESTROY "pthread_rwlock_destroy"
#define EVOWRAPPER_PTHREAD_RWLOCK_RDLOCK "pthread_rwlock_rdlock"
#define EVOWRAPPER_PTHREAD_RWLOCK_TRYRDLOCK "pthread_rwlock_tryrdlock"
#define EVOWRAPPER_PTHREAD_RWLOCK_WRLOCK "pthread_rwlock_wrlock"
#define EVOWRAPPER_PTHREAD_RWLOCK_TRYWRLOCK "pthread_rwlock_trywrlock"
#define EVOWRAPPER_PTHREAD_RWLOCK_UNLOCK "pthread_rwlock_unlock"
#define EVOWRAPPER_PTHREAD_RWLOCKATTR_INIT "pthread_rwlockattr_init"
#define EVOWRAPPER_PTHREAD_RWLOCKATTR_DESTROY "pthread_rwlockattr_destroy"
#define EVOWRAPPER_PTHREAD_RWLOCKATTR_SETPSHARED "pthread_rwlockattr_setpshared"

EVO_APICALL INT32 evo_pthread_rwlock_init(pthread_rwlock_t *rwlock, const pthread_rwlockattr_t *attr);
EVO_APICALL INT32 evo_pthread_rwlock_destroy(pthread_rwlock_t *rwlock);
EVO_APICALL INT32 evo_pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);
EVO_APICALL INT32 evo_pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock);
EVO_APICALL INT32 evo_pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);
EVO_APICALL INT32 evo_pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock);
EVO_APICALL INT32 evo_pthread_rwlock_unlock(pthread_rwlock_t *rwlock);
EVO_APICALL INT32 evo_pthread_rwlockattr_init(pthread_rwlockattr_t *attr);
EVO_APICALL INT32 evo_pthread_rwlockattr_destroy(pthread_rwlockattr_t *attr);
EVO_APICALL INT32 evo_pthread_rwlockattr_setpshared(pthread_rwlockattr_t *attr, INT32 pshared);

// pthread-spinlock
#define EVOWRAPPER_PTHREAD_SPINLOCK_INIT "pthread_spin_init"
#define EVOWRAPPER_PTHREAD_SPINLOCK_DESTROY "pthread_spin_destroy"
#define EVOWRAPPER_PTHREAD_SPINLOCK_LOCK "pthread_spin_lock"
#define EVOWRAPPER_PTHREAD_SPINLOCK_TRYLOCK "pthread_spin_trylock"
#define EVOWRAPPER_PTHREAD_SPINLOCK_UNLOCK "pthread_spin_unlock"

EVO_APICALL INT32 evo_pthread_spin_init(pthread_spinlock_t *lock, INT32 pshared);
EVO_APICALL INT32 evo_pthread_spin_destroy(pthread_spinlock_t *lock);
EVO_APICALL INT32 evo_pthread_spin_lock(pthread_spinlock_t *lock);
EVO_APICALL INT32 evo_pthread_spin_trylock(pthread_spinlock_t *lock);
EVO_APICALL INT32 evo_pthread_spin_unlock(pthread_spinlock_t *lock);

// pthread-barrier
#define EVOWRAPPER_PTHREAD_BARRIER_INIT "pthread_barrier_init"
#define EVOWRAPPER_PTHREAD_BARRIER_DESTROY "pthread_barrier_destroy"
#define EVOWRAPPER_PTHREAD_BARRIER_WAIT "pthread_barrier_wait"

EVO_APICALL INT32 evo_pthread_barrier_init(pthread_barrier_t *barrier, const pthread_barrierattr_t *attr, UINT32 count);
EVO_APICALL INT32 evo_pthread_barrier_destroy(pthread_barrier_t *barrier);
EVO_APICALL INT32 evo_pthread_barrier_wait(pthread_barrier_t *barrier);

// dl Link with -ldl
#define EVOWRAPPER_DLOPEN "dlopen"
#define EVOWRAPPER_DLSYM "dlsym"
#define EVOWRAPPER_DLCLOSE "dlclose"
#define EVOWRAPPER_DLADDR "dladdr"

EVO_APICALL VOID* evo_dlopen(const CHAR *filename, INT32 flag);
EVO_APICALL VOID* evo_dlsym(VOID *handle, const CHAR *symbol);
EVO_APICALL INT32 evo_dlclose(VOID *handle);
EVO_APICALL INT32 evo_dladdr(const VOID *address, VOID *info);

EVO_END_DECLS

#endif // EVO_EVOWRAPPER_H
