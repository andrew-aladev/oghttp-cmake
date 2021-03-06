// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#if !defined(DECLARATION_CONSTANTS_H)
#define DECLARATION_CONSTANTS_H

#include <libxml/parser.h>
#include <stdlib.h>

int read_constants(const xmlDocPtr document, char*** constants_ptr, size_t* constants_length_ptr);

#endif // DECLARATION_CONSTANTS_H
