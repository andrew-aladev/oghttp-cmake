// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#if !defined(DECLARATION_GROUP_MAIN_H)
#define DECLARATION_GROUP_MAIN_H

#include <libxml/parser.h>
#include <stdbool.h>

int read_groups(const xmlDocPtr document, bool* allowed_bytes);

#endif // DECLARATION_GROUP_MAIN_H
