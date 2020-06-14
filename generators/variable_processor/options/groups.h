// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#if !defined(OPTIONS_GROUPS_H)
#define OPTIONS_GROUPS_H

#include <libxml/parser.h>
#include <stdbool.h>

int read_groups(const xmlDocPtr document, bool* allowed_bytes_result);

#endif // OPTIONS_GROUPS_H
