// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

// This file was generated, do not edit manually.

// It may not be possible to run generator while cross compiling.
// So generated file should be distributed with its template.

#include "main.h"

const ogh_processor_state_t OGH_PROCESSOR_METHOD_0_9_INITIAL_STATE = 0;

// clang-format off

const ogh_byte_t OGH_PROCESSOR_METHOD_0_9_CONSTANT_BYTES[] = {
0x47,
0x45,
0x54};

// clang-format on

const size_t OGH_PROCESSOR_METHOD_0_9_CONSTANT_LENGTH = 3;

extern inline ogh_processor_state_t ogh_processor_method_0_9_get_next_state(ogh_processor_state_t state, ogh_byte_t byte);
extern inline bool                  ogh_processor_method_0_9_is_finished(ogh_processor_state_t state);
