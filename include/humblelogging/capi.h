#ifndef HL_CAPI_H
#define HL_CAPI_H

#include "defines.h"

#ifdef __cplusplus
extern "C" {
#endif

// Types
typedef void* LOGGERHANDLE;

// Functions
HL_EXPORT_C_API LOGGERHANDLE hl_logger_create(const char *name);
HL_EXPORT_C_API int hl_logger_would_log(LOGGERHANDLE handle, int level);
HL_EXPORT_C_API void hl_logger_log(LOGGERHANDLE handle, int level, const char *message, int line, const char *file, const char *func);

// Macros for easy use within C/C++ code.
#define HUMBLE_LOGGER(L, N) static LOGGERHANDLE L = hl_get_logger(N)

#ifdef HUMBLE_INCLUDE_PRETTY_FUNCTION
#define HUMBLE_LOG(L,S,LL) \
  do { \
    if (hl_logger_would_log(L, LL)) { \
      hl_logger_log(L, LL, S, __LINE__, __FILE__, __FUNCNAME__); \
    } \
  } \
  while (false)
#else
#define HUMBLE_LOG(L,S,LL) \
  do { \
    if (hl_logger_would_log(L, LL)) { \
      hl_logger_log(L, LL, S, __LINE__, __FILE__, 0); \
    } \
  } \
  while (false)
#endif

#ifdef __cplusplus
}
#endif

#endif