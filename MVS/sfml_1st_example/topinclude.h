#ifndef _DEF_TOPINCLUDE_H_
#define _DEF_TOPINCLUDE_H_

#if defined(_MSC_VER)
#   define _STASIS_WINDOWS
#   define _STASIS_OSNAME "Windows"
#endif

#ifdef __linux__
#   define _PBSTEXTANALYSIS_LINUX
#   define _PBSTEXTANALYSIS_OSNAME "Linux"
#endif

#ifdef _STASIS_LINUX
#include <assert.h>
#define __min(x,y) (((x)<=(y))? (x) : (y))
#define _ASSERTE assert
#define _ASSERT assert
#define sscanf_s(a,b,c) sscanf(a,b,c) 
#define strcpy_s(a,l,b) strcpy(a,b)
#define strncpy_s(a,l,b,n) strncpy(a,b,n)
#define strcat_s(a,l,b) strcat(a,b)
#define strncat_s(strDest, numberOfElements, strSource, count) strncat(strDest, strSource, count)
#define strtok_s(a,delim,c) strtok(a,delim)
#define _stricmp strcasecmp
#define _strnicmp strncasecmp
#define _strdup strdup
#define sprintf_s(buffer, l, ...) snprintf(buffer, l, ##__VA_ARGS__)
#define StrStr(string, substring) strcasestr(string, substring)
#define StrStrI(string, substring) strcasestr(string, substring)
#define _strdup strdup
#endif

#endif  //_DEF_TOPINCLUDE_H_
