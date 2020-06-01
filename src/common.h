// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#if !defined(OGH_COMMON_H)
#define OGH_COMMON_H

#include <stdint.h>
#include <stdlib.h>

typedef uint8_t ogh_result_t;
typedef uint8_t ogh_byte_t;

// Unified processor state type.
typedef size_t ogh_processor_state_t;

#define OGH_MAX_BYTE UINT8_MAX

#endif // OGH_COMMON_H
