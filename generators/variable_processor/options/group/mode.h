// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#if !defined(OPTIONS_GROUP_MODE_H)
#define OPTIONS_GROUP_MODE_H

#include <libxml/parser.h>
#include <stdint.h>

enum {
  GROUP_MODE_INCLUDE,
  GROUP_MODE_EXCLUDE
};
typedef uint8_t group_mode_t;

int read_group_mode(const xmlNodePtr group, group_mode_t* group_mode_ptr);

#endif // OPTIONS_GROUP_MODE_H
