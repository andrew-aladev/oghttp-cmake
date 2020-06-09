// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#if !defined(OPTIONS_CONSTANT_H)
#define OPTIONS_CONSTANT_H

#include <libxml/HTMLparser.h>

int read_constant(const htmlDocPtr document, char** constant_ptr);

#endif // OPTIONS_CONSTANT_H
