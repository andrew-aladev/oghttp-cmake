// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "alphabet.h"
#include "data.h"
#include "max_state.h"
#include "min_state_bits.h"
#include "next_state_by_last_symbols.h"
#include "prefix.h"

int main()
{
  print_data();

  // -- alphabet --

  uint8_t* alphabet;
  uint8_t* symbol_by_bytes;
  size_t   alphabet_length;

  int result = init_alphabet(&alphabet, &symbol_by_bytes, &alphabet_length);
  if (result != 0) {
    return 1;
  }

  print_alphabet_length(alphabet_length);
  print_symbol_by_bytes(alphabet, symbol_by_bytes, alphabet_length);

  free(alphabet);

  // -- prefixes --

  size_t prefixes_length;

  result = init_prefixes(&prefixes_length);
  if (result != 0) {
    free(symbol_by_bytes);
    return 2;
  }

  // -- max state --

  size_t max_state;
  init_max_state(&max_state, prefixes_length);
  print_max_state(max_state);

  // -- min state bits --

  result = print_min_state_bits(max_state);
  if (result != 0) {
    free(symbol_by_bytes);
    return 3;
  }

  // -- next state by last symbols --

  size_t* next_state_by_last_symbols;
  size_t  next_state_by_last_symbols_length;

  result = init_next_state_by_last_symbols(
    &next_state_by_last_symbols, &next_state_by_last_symbols_length,
    symbol_by_bytes, alphabet_length, max_state);

  free(symbol_by_bytes);

  if (result != 0) {
    return 4;
  }

  print_next_state_by_last_symbols(next_state_by_last_symbols, next_state_by_last_symbols_length);

  free(next_state_by_last_symbols);

  return 0;
}
