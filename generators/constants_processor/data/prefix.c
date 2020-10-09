// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "prefix.h"

#include <string.h>

#include "print.h"

typedef struct {
  const char* constant;
  size_t      length;
} prefix_t;

// We need to check whether prefix is not equal to any constant.
static inline bool is_prefix(const char** constants, size_t constants_length, const char* prefix_constant,
                             size_t prefix_length)
{
  for (size_t index = 0; index < constants_length; index++) {
    const char* constant = constants[index];

    if (strlen(constant) == prefix_length && strncmp(constant, prefix_constant, prefix_length) == 0) {
      return false;
    }
  }

  return true;
}

static inline bool has_prefix(const prefix_t* prefixes, size_t prefixes_length, const char* prefix_constant,
                              size_t prefix_length)
{
  for (size_t index = 0; index < prefixes_length; index++) {
    const prefix_t* prefix = &prefixes[index];

    if (prefix->length == prefix_length && strncmp(prefix->constant, prefix_constant, prefix_length) == 0) {
      return true;
    }
  }

  return false;
}

static inline void add_prefix(prefix_t* prefixes, size_t* prefixes_length_ptr, const char* prefix_constant,
                              size_t prefix_length)
{
  prefix_t* prefix = &prefixes[*prefixes_length_ptr];
  (*prefixes_length_ptr)++;

  prefix->constant = prefix_constant;
  prefix->length   = prefix_length;
}

int init_prefixes_length(const char** constants, size_t constants_length, size_t* prefixes_length_ptr)
{
  // We can limit max possible prefixes length.
  size_t max_prefixes_length = 0;

  for (size_t index = 0; index < constants_length; index++) {
    max_prefixes_length += strlen(constants[index]) - 1;
  }

  size_t max_prefixes_size = max_prefixes_length * sizeof(prefix_t);

  prefix_t* prefixes = malloc(max_prefixes_size);
  if (prefixes == NULL) {
    PRINTF_ERROR("failed to allocate memory for prefixes, size: %zu", max_prefixes_size);
    return 1;
  }

  size_t prefixes_length = 0;

  for (size_t index = 0; index < constants_length; index++) {
    const char* prefix_constant = constants[index];

    for (size_t prefix_length = 1; prefix_length < strlen(prefix_constant); prefix_length++) {
      if (!is_prefix(constants, constants_length, prefix_constant, prefix_length)) {
        continue;
      }

      if (!has_prefix(prefixes, prefixes_length, prefix_constant, prefix_length)) {
        add_prefix(prefixes, &prefixes_length, prefix_constant, prefix_length);
      }
    }
  }

  free(prefixes);

  *prefixes_length_ptr = prefixes_length;

  return 0;
}
