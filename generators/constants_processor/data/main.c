// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "main.h"

#include "alphabet.h"
#include "constants.h"
#include "next_state.h"
#include "prefix.h"
#include "state.h"

int process_data(const char** constants, size_t constants_length)
{
  size_t prefixes_length;
  if (init_prefixes_length(constants, constants_length, &prefixes_length) != 0) {
    return 1;
  }

  print_constants_length(constants_length);

  if (print_constant_states(constants, constants_length) != 0) {
    return 2;
  }

  size_t max_state = get_max_state(constants_length, prefixes_length);
  print_max_state(max_state);

  if (print_min_state_bits(max_state) != 0) {
    return 3;
  }

  uint8_t* alphabet;
  size_t   alphabet_length;
  uint8_t* symbol_by_bytes;

  int result = init_alphabet(constants, constants_length, &alphabet, &alphabet_length, &symbol_by_bytes);

  if (result != 0) {
    return 4;
  }

  print_alphabet_length(alphabet_length);
  print_symbol_by_bytes(alphabet, alphabet_length, symbol_by_bytes);

  result = print_next_state_by_last_symbols(constants, constants_length, symbol_by_bytes, alphabet_length, max_state);

  free(alphabet);
  free(symbol_by_bytes);

  if (result != 0) {
    return 5;
  }

  return 0;
}
