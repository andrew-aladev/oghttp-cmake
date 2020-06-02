// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "alphabet.h"

#include <string.h>

#include "options.h"
#include "print.h"

#define ALPHABET_MAX_LENGTH UINT8_MAX + 1

#define SYMBOL_BY_BYTES_LENGTH ALPHABET_MAX_LENGTH
#define UNDEFINED_SYMBOL SYMBOL_BY_BYTES_LENGTH - 1

static inline bool has_symbol_for_byte(const uint8_t* symbol_by_bytes, uint8_t byte)
{
  return symbol_by_bytes[byte] != UNDEFINED_SYMBOL;
}

static inline void add_symbol(uint8_t* alphabet, uint8_t* symbol_by_bytes, size_t* alphabet_length_ptr, uint8_t byte)
{
  uint8_t symbol = *alphabet_length_ptr;
  (*alphabet_length_ptr)++;

  alphabet[symbol]      = byte;
  symbol_by_bytes[byte] = symbol;
}

static inline bool is_alphabet_full(size_t alphabet_length)
{
  return alphabet_length == ALPHABET_MAX_LENGTH;
}

int init_alphabet(uint8_t** alphabet_ptr, uint8_t** symbol_by_bytes_ptr, size_t* alphabet_length_ptr)
{
  *alphabet_ptr = malloc(ALPHABET_MAX_LENGTH);
  if (*alphabet_ptr == NULL) {
    PRINT_ERROR("failed to allocate memory for alphabet");
    return 1;
  }

  *symbol_by_bytes_ptr = malloc(SYMBOL_BY_BYTES_LENGTH);
  if (*symbol_by_bytes_ptr == NULL) {
    PRINT_ERROR("failed to allocate memory for symbol by bytes");
    free(*alphabet_ptr);
    return 2;
  }

  size_t index;

  for (index = 0; index < SYMBOL_BY_BYTES_LENGTH; index++) {
    (*symbol_by_bytes_ptr)[index] = UNDEFINED_SYMBOL;
  }

  *alphabet_length_ptr = 0;

  for (index = 0; index < OGH_CONSTANTS_LENGTH; index++) {
    const char* constant = OGH_CONSTANTS[index];

    for (size_t jndex = 0; jndex < strlen(constant); jndex++) {
      uint8_t byte = constant[jndex];

      if (!has_symbol_for_byte(*symbol_by_bytes_ptr, byte)) {
        add_symbol(*alphabet_ptr, *symbol_by_bytes_ptr, alphabet_length_ptr, byte);

        if (is_alphabet_full(*alphabet_length_ptr)) {
          // We don't need other constants, alphabet is already full.
          return 0;
        }
      }
    }
  }

  return 0;
}

void print_alphabet_length(size_t alphabet_length)
{
  PRINT_LENGTH(alphabet_length);
  PRINT_GLUE();
}

#define SYMBOL_BY_BYTE_TEMPLATE "[%u] = %u"

#define PRINT_SYMBOL_BY_BYTE(byte, symbol) printf(SYMBOL_BY_BYTE_TEMPLATE, byte, symbol);

void print_symbol_by_bytes(const uint8_t* alphabet, const uint8_t* symbol_by_bytes, size_t alphabet_length)
{
  INITIALIZE_SPACERS();

  for (size_t index = 0; index < alphabet_length; index++) {
    uint8_t byte = alphabet[index];

    PRINT_SPACER();
    PRINT_SYMBOL_BY_BYTE(byte, symbol_by_bytes[byte]);
  }

  PRINT_GLUE();
}
