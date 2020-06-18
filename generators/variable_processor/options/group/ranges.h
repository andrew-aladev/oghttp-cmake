// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#if !defined(OPTIONS_GROUP_RANGES_H)
#define OPTIONS_GROUP_RANGES_H

#include <libxml/parser.h>
#include <stdbool.h>

int read_group_range_bytes(const xmlDocPtr document, const xmlNodePtr group, bool* range_bytes);

#endif // OPTIONS_GROUP_RANGES_H
