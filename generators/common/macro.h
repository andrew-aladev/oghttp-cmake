// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#if !defined(MACRO_H)
#define MACRO_H

#if defined(__GNUC__)
#define UNUSED(x) x __attribute__((__unused__))
#else
#define UNUSED(x) x
#endif

#endif // MACRO_H
