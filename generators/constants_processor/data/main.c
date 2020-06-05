// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "main.h"

#include "alphabet.h"
#include "constants.h"
#include "prefix.h"
#include "state.h"

int process_data(const char** constants, size_t constants_length)
{
  size_t prefixes_length;
  if (init_prefixes_length(constants, constants_length, &prefixes_length) != 0) {
    return 1;
  }

  // Constants length.
  print_constants_length(constants_length);

  // Constant states.
  if (print_constant_states(constants, constants_length) != 0) {
    return 2;
  }

  // Max state.
  size_t max_state = get_max_state(constants_length, prefixes_length);
  print_max_state(max_state);

  // Min state bits.
  if (print_min_state_bits(max_state) != 0) {
    return 3;
  }

  uint8_t* alphabet;
  size_t   alphabet_length;
  uint8_t* symbol_by_bytes;

  if (init_alphabet(constants, constants_length, &alphabet, &alphabet_length, &symbol_by_bytes) != 0) {
    return 4;
  }

  // Alphabet length.
  print_alphabet_length(alphabet_length);

  // Symbol by bytes.
  print_symbol_by_bytes(alphabet, alphabet_length, symbol_by_bytes);

  free(alphabet);
  free(symbol_by_bytes);

  return 0;
}
