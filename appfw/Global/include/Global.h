/**
 * @file Global.h
 * @brief Global definitions
 */

#ifndef EVO_GLOBAL_H
#define EVO_GLOBAL_H

/* platform */
#if defined(_WIN32) || defined(_WIN32_WCE)
# ifdef EVO_DLL_EXPORTS
#  define EVO_APICALL __declspec(dllexport)
# elif defined(EVO_DLL_IMPORTS)
#  define EVO_APICALL __declspec(dllimport)
# else
#  define EVO_APICALL
# endif
#elif defined(linux) || defined (__linux) || defined(__GNUC__)
# define EVO_APICALL __attribute__((visibility("default")))
#else
# define EVO_APICALL
#endif

// TODO using namespace EVO;
/* namespace */
#if defined(__cplusplus) && defined(EVO_USING_NAMESPASE)
# define BEGIN_NAMESPACE_EVO namespace EVO {
# define END_NAMESPACE_EVO }
# define USING_NAMESPACE_EVO using namespace EVO;
# define USING_NAMESPACE_FROMEVO(name) using EVO::name;
#else
# define BEGIN_NAMESPACE_EVO
# define END_NAMESPACE_EVO
# define USING_NAMESPACE_EVO
# define USING_NAMESPACE_FROMEVO(name)
#endif

/* extern */
#ifdef	__cplusplus
# define EVO_BEGIN_DECLS extern "C" {
# define EVO_END_DECLS }
# define EVO_DECLS_SINGLE extern "C"
# define EVO_DECLS extern
#else
# define EVO_BEGIN_DECLS
# define EVO_END_DECLS
# define EVO_DECLS_SINGLE
# define EVO_DECLS
#endif

/* define */
#define EVO_CONFIG(x) (defined CONFIG_##x && CONFIG_##x)
#define EVO_UNUSED(x) ((void)(x))
#define EVO_UNUSED_X(x) (static_cast<void>(x))
#define EVO_UNUSED_PARAM __attribute__((unused))
#define EVO_DISABLE_COPY(Class) \
    Class(const Class&); \
    Class& operator=(const Class&);

/* word */
// #include <bits/wordsize.h>
#if defined(__x86_64__) && !defined(__ILP32__)
# define EVO_WORDSIZE 64
#else
# define EVO_WORDSIZE 32
#endif

/* type: builtin */
#include <wchar.h>
typedef void VOID;
typedef char CHAR;
typedef signed char SCHAR; // signed char
typedef unsigned char UCHAR;
typedef wchar_t WCHAR; // WCHAR zero = L'\0';
typedef short int SHORT;
typedef unsigned short int USHORT;
typedef long int LONG;
typedef unsigned long int ULONG;
typedef long long int LLONG;
typedef unsigned long long int ULLONG;
typedef float FLOAT;
typedef double DOUBLE;
typedef long double LDOUBLE;

/* type: word */
typedef unsigned short int WORD;
typedef unsigned int DWORD;

/* type: bool */
// #include <stdbool.h>
#ifndef __cplusplus
# define BOOL int
# define TRUE 1
# define FALSE 0
#else
# define BOOL bool
# define TRUE true
# define FALSE false
#endif

/* type: int */
// #include <stdint.h>
typedef signed char INT8;
typedef unsigned char UINT8;
typedef short int INT16;
typedef unsigned short int UINT16;
typedef int INT32;
typedef unsigned int UINT32;
#if EVO_WORDSIZE == 64
typedef long int INT64;
typedef unsigned long int UINT64;
#else
__extension__
typedef long long int INT64;
__extension__
typedef unsigned long long int UINT64;
#endif

/* type: limit */
// #include <stdint.h>
#if EVO_WORDSIZE == 64
# define EVO_INT64_C(c) c##L
# define EVO_UINT64_C(c) c##UL
#else
# define EVO_INT64_C(c) c##LL
# define EVO_UINT64_C(c) c##ULL
#endif
#define EVO_INT8_MIN (-128)
#define EVO_INT16_MIN (-32767-1)
#define EVO_INT32_MIN (-2147483647-1)
#define EVO_INT64_MIN (-EVO_INT64_C(9223372036854775807)-1)
#define EVO_INT8_MAX (127)
#define EVO_INT16_MAX (32767)
#define EVO_INT32_MAX (2147483647)
#define EVO_INT64_MAX (EVO_INT64_C(9223372036854775807))
#define EVO_UINT8_MAX (255)
#define EVO_UINT16_MAX (65535)
#define EVO_UINT32_MAX (4294967295U)
#define EVO_UINT64_MAX (EVO_UINT64_C(18446744073709551615))

/* type: others */
#include <sys/types.h>
typedef size_t SIZE_T;
typedef ssize_t SSIZE_T;
typedef mode_t MODE_T;
typedef pid_t PID_T;
typedef pthread_t TID_T;
typedef uid_t UID_T;
typedef gid_t GID_T;
typedef off_t OFF_T;
// #include <mqueue.h>
typedef int MQD_T;

/* app */
typedef unsigned int AppId;

#endif // EVO_GLOBAL_H
