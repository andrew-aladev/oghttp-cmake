// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "next_state_by_last_symbols.h"

#include <string.h>

#include "options.h"
#include "print.h"

#define INITIAL_STATE OGH_CONSTANTS_LENGTH

// We need to check whether current prefix matches constant.
static inline bool find_state_from_constants(size_t* state_ptr, const char* constant, size_t prefix_length)
{
  for (size_t index = 0; index < OGH_CONSTANTS_LENGTH; index++) {
    const char* target_constant = OGH_CONSTANTS[index];

    if (prefix_length == strlen(target_constant) && strncmp(constant, target_constant, prefix_length) == 0) {
      *state_ptr = index;
      return true;
    }
  }

  return false;
}

int init_next_state_by_last_symbols(
  size_t** next_state_by_last_symbols_ptr, size_t* next_state_by_last_symbols_length_ptr,
  const uint8_t* symbol_by_bytes, size_t alphabet_length, size_t max_state)
{
  // Each state has alphabet length of possible last symbols.
  *next_state_by_last_symbols_length_ptr = (max_state + 1) * alphabet_length;

  *next_state_by_last_symbols_ptr = malloc(*next_state_by_last_symbols_length_ptr * sizeof(size_t));
  if (*next_state_by_last_symbols_ptr == NULL) {
    PRINT_ERROR("failed to allocate memory for next state by last symbols");
    return 1;
  }

  // Initialize all next states with initial state.
  for (size_t index = 0; index < *next_state_by_last_symbols_length_ptr; index++) {
    (*next_state_by_last_symbols_ptr)[index] = INITIAL_STATE;
  }

  size_t global_state = INITIAL_STATE;

  for (size_t index = 0; index < OGH_CONSTANTS_LENGTH; index++) {
    // Starting with empty string and initial state.
    const char* constant = OGH_CONSTANTS[index];
    size_t      state    = INITIAL_STATE;

    for (size_t jndex = 0; jndex < strlen(constant); jndex++) {
      uint8_t byte              = constant[jndex];
      uint8_t last_symbol       = symbol_by_bytes[byte];
      size_t  last_symbol_index = state * alphabet_length + last_symbol;
      size_t  last_symbol_state = (*next_state_by_last_symbols_ptr)[last_symbol_index];

      if (last_symbol_state != INITIAL_STATE) {
        state = last_symbol_state;
        continue;
      }

      if (!find_state_from_constants(&state, constant, jndex + 1)) {
        if (global_state >= max_state) {
          PRINT_ERROR("global state should be less than max state");
          free(*next_state_by_last_symbols_ptr);
          return 2;
        }

        state = ++global_state;
      }

      (*next_state_by_last_symbols_ptr)[last_symbol_index] = state;
    }
  }

  if (global_state != max_state) {
    PRINT_ERROR("global state is not equal to max state");
    free(*next_state_by_last_symbols_ptr);
    return 3;
  }

  return 0;
}

#define NEXT_STATE_BY_LAST_SYMBOL_TEMPLATE "[%zu] = %zu"

#define PRINT_NEXT_STATE_BY_LAST_SYMBOL(index, next_state) printf(NEXT_STATE_BY_LAST_SYMBOL_TEMPLATE, index, next_state);

void print_next_state_by_last_symbols(const size_t* next_state_by_last_symbols, size_t next_state_by_last_symbols_length)
{
  INITIALIZE_SPACERS(true);

  for (size_t index = 0; index < next_state_by_last_symbols_length; index++) {
    size_t next_state = next_state_by_last_symbols[index];
    if (next_state == INITIAL_STATE) {
      continue;
    }

    PRINT_SPACER();
    PRINT_NEXT_STATE_BY_LAST_SYMBOL(index, next_state);
  }

  PRINT_GLUE();
}
