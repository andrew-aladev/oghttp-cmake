// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#if !defined(OPTIONS_GROUP_BYTE_H)
#define OPTIONS_GROUP_BYTE_H

#include <libxml/parser.h>
#include <stdint.h>

int read_byte_value(const xmlNodePtr node, uint8_t* byte_value_ptr);

#endif // OPTIONS_GROUP_BYTE_H
