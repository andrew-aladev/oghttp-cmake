// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

// This file was generated, do not edit manually.

// It may not be possible to run generator while cross compiling.
// So generated file should be distributed with its template.

#if !defined(OGH_PROCESSOR_METHOD_0_9_H)
#define OGH_PROCESSOR_METHOD_0_9_H

#include <stdbool.h>

#include "../../../common.h"
#include "../../../log.h"

extern const ogh_processor_state_t OGH_PROCESSOR_METHOD_0_9_INITIAL_STATE;

extern const ogh_byte_t            OGH_PROCESSOR_METHOD_0_9_CONSTANT_BYTES[];
extern const ogh_processor_state_t OGH_PROCESSOR_METHOD_0_9_CONSTANT_LENGTH;

inline ogh_processor_state_t ogh_processor_method_0_9_get_next_state(ogh_processor_state_t state, ogh_byte_t byte)
{
  if (OGH_PROCESSOR_METHOD_0_9_CONSTANT_BYTES[state] != byte) {
    OGH_LOG_ERROR("method_0_9 processor received invalid byte: %u", byte);
    return OGH_PROCESSOR_METHOD_0_9_INITIAL_STATE;
  }

  return state + 1;
}

inline bool ogh_processor_method_0_9_is_finished(ogh_processor_state_t state)
{
  return state == OGH_PROCESSOR_METHOD_0_9_CONSTANT_LENGTH;
}

#endif // OGH_PROCESSOR_METHOD_0_9_H
