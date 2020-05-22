// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "prefix.h"

#include <string.h>

#include "options.h"
#include "print.h"

typedef struct {
  const char* constant;
  size_t      length;
} prefix_t;

// We need to check whether prefix is not equal to any constant.
static inline bool is_prefix(const char* constant, size_t prefix_length)
{
  for (size_t index = 0; index < OGH_CONSTANTS_LENGTH; index++) {
    const char* target_constant = OGH_CONSTANTS[index];

    if (strlen(target_constant) == prefix_length && strncmp(target_constant, constant, prefix_length) == 0) {
      return false;
    }
  }

  return true;
}

static inline bool has_prefix(const prefix_t* prefixes, size_t prefixes_length, const char* constant, size_t prefix_length)
{
  for (size_t index = 0; index < prefixes_length; index++) {
    const prefix_t* prefix = &prefixes[index];

    if (prefix->length == prefix_length && strncmp(prefix->constant, constant, prefix_length) == 0) {
      return true;
    }
  }

  return false;
}

static inline void add_prefix(prefix_t* prefixes, size_t* prefixes_length_ptr, const char* constant, size_t prefix_length)
{
  prefix_t* prefix = &prefixes[*prefixes_length_ptr];
  (*prefixes_length_ptr)++;

  prefix->constant = constant;
  prefix->length   = prefix_length;
}

int init_prefixes(size_t* prefixes_length_ptr)
{
  // We can limit max possible prefixes length.
  size_t max_prefixes_length = 0;

  for (size_t index = 0; index < OGH_CONSTANTS_LENGTH; index++) {
    max_prefixes_length += strlen(OGH_CONSTANTS[index]) - 1;
  }

  prefix_t* prefixes = malloc(max_prefixes_length * sizeof(prefix_t));
  if (prefixes == NULL) {
    PRINT_ERROR("failed to allocate memory for prefixes");
    return 1;
  }

  *prefixes_length_ptr = 0;

  for (size_t index = 0; index < OGH_CONSTANTS_LENGTH; index++) {
    const char* constant = OGH_CONSTANTS[index];

    for (size_t prefix_length = 1; prefix_length < strlen(constant); prefix_length++) {
      if (!is_prefix(constant, prefix_length)) {
        continue;
      }

      if (!has_prefix(prefixes, *prefixes_length_ptr, constant, prefix_length)) {
        add_prefix(prefixes, prefixes_length_ptr, constant, prefix_length);
      }
    }
  }

  free(prefixes);

  return 0;
}
