// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#if !defined(CONSTANTS_H)
#define CONSTANTS_H

#include <libxml/xpath.h>
#include <stdbool.h>

int print_constants(const xmlNodeSetPtr nodes, size_t nodes_length, bool is_first_file);

#endif // CONSTANTS_H
