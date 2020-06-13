// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#if !defined(OPTIONS_LENGTH_H)
#define OPTIONS_LENGTH_H

#include <libxml/parser.h>
#include <stdlib.h>

int read_length(const xmlDocPtr document, const char* xpath, size_t* length_ptr);

#endif // OPTIONS_LENGTH_H
