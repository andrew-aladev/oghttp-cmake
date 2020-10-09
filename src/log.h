// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#if !defined(OGH_LOG_H)
#define OGH_LOG_H

#include <stdio.h>

// Relative file path can be provided during each source file compilation.
#ifndef __RELATIVE_FILE_PATH__
#define __RELATIVE_FILE_PATH__ __FILE__
#endif

#define _OGH_LOG(target, ...)                                                 \
  fprintf(target, "%s %s:%u - ", __func__, __RELATIVE_FILE_PATH__, __LINE__); \
  fprintf(target, __VA_ARGS__);                                               \
  fputs("\n", target);

#define OGH_LOG_ERROR(...) _OGH_LOG(stderr, __VA_ARGS__)

#endif // OGH_LOG_H
