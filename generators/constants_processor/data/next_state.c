// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "next_state.h"

#include <string.h>

#include "print.h"

// We need to check whether current prefix matches existing constant.
static inline bool find_state_from_constants(
  const char** constants, size_t constants_length,
  size_t* state_ptr, const char* prefix_constant, size_t prefix_length)
{
  for (size_t index = 0; index < constants_length; index++) {
    const char* constant = constants[index];

    if (strlen(constant) == prefix_length && strncmp(constant, prefix_constant, prefix_length) == 0) {
      *state_ptr = index;
      return true;
    }
  }

  return false;
}

static inline int init_next_state_by_last_symbols(
  const char** constants, size_t constants_length,
  const uint8_t* symbol_by_bytes, size_t alphabet_length, size_t initial_state, size_t max_state,
  size_t** next_state_by_last_symbols_ptr, size_t* next_state_by_last_symbols_length_ptr)
{
  // Each state has alphabet length of possible last symbols.
  size_t next_state_by_last_symbols_length = (max_state + 1) * alphabet_length;

  size_t* next_state_by_last_symbols = malloc(next_state_by_last_symbols_length * sizeof(size_t));
  if (next_state_by_last_symbols == NULL) {
    PRINT_ERROR("failed to allocate memory for next state by last symbols");
    return 1;
  }

  // Initialize all next states with initial state.
  for (size_t index = 0; index < next_state_by_last_symbols_length; index++) {
    next_state_by_last_symbols[index] = initial_state;
  }

  size_t global_state = initial_state;

  for (size_t index = 0; index < constants_length; index++) {
    // Starting with empty string and initial state.
    const char* prefix_constant = constants[index];
    size_t      state           = initial_state;

    for (size_t jndex = 0; jndex < strlen(prefix_constant); jndex++) {
      uint8_t byte              = prefix_constant[jndex];
      uint8_t last_symbol       = symbol_by_bytes[byte];
      size_t  last_symbol_index = state * alphabet_length + last_symbol;
      size_t  last_symbol_state = next_state_by_last_symbols[last_symbol_index];

      if (last_symbol_state != initial_state) {
        state = last_symbol_state;
        continue;
      }

      bool is_constant_state_exist = find_state_from_constants(
        constants, constants_length,
        &state, prefix_constant, jndex + 1);

      if (!is_constant_state_exist) {
        if (global_state >= max_state) {
          PRINT_ERROR("global state should be less than max state");
          free(next_state_by_last_symbols);
          return 2;
        }

        state = ++global_state;
      }

      next_state_by_last_symbols[last_symbol_index] = state;
    }
  }

  if (global_state != max_state) {
    PRINT_ERROR("global state is not equal to max state");
    free(next_state_by_last_symbols);
    return 3;
  }

  *next_state_by_last_symbols_ptr        = next_state_by_last_symbols;
  *next_state_by_last_symbols_length_ptr = next_state_by_last_symbols_length;

  return 0;
}

#define NEXT_STATE_BY_LAST_SYMBOL_TEMPLATE "[%zu] = %zu"

int print_next_state_by_last_symbols(
  const char** constants, size_t constants_length,
  const uint8_t* symbol_by_bytes, size_t alphabet_length, size_t max_state)
{
  size_t initial_state = constants_length;

  size_t* next_state_by_last_symbols;
  size_t  next_state_by_last_symbols_length;

  int result = init_next_state_by_last_symbols(
    constants, constants_length,
    symbol_by_bytes, alphabet_length, initial_state, max_state,
    &next_state_by_last_symbols, &next_state_by_last_symbols_length);

  if (result != 0) {
    return 1;
  }

  INITIALIZE_SPACERS(true);

  for (size_t index = 0; index < next_state_by_last_symbols_length; index++) {
    size_t next_state = next_state_by_last_symbols[index];
    if (next_state == initial_state) {
      continue;
    }

    PRINT_SPACER();
    PRINTF(NEXT_STATE_BY_LAST_SYMBOL_TEMPLATE, index, next_state);
  }

  PRINT_GLUE();

  return 0;
}
