#ifndef _DEF_TOPINCLUDE_H_
#define _DEF_TOPINCLUDE_H_

#if defined(_MSC_VER)
#   define _STASIS_WINDOWS
#   define _STASIS_OSNAME "Windows"
#endif

#ifdef __linux__
#   define _STASIS_LINUX
#   define _STASIS_OSNAME "Linux"
#endif

#ifdef _STASIS_LINUX
#include <assert.h>
#endif

#ifdef _STASIS_LINUX
#   define STATIS_ROOT_PATH 
#endif
#ifdef _STASIS_WINDOWS
#   define STATIS_ROOT_PATH "../../"
#endif

#endif  //_DEF_TOPINCLUDE_H_
