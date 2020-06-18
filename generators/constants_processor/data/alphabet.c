// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "alphabet.h"

#include <string.h>

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

int init_alphabet(
  const char** constants, size_t constants_length,
  uint8_t** alphabet_ptr, size_t* alphabet_length_ptr, uint8_t** symbol_by_bytes_ptr)
{
  uint8_t* alphabet = malloc(ALPHABET_MAX_LENGTH);
  if (alphabet == NULL) {
    PRINTF_ERROR("failed to allocate memory for alphabet, size: %u", ALPHABET_MAX_LENGTH);
    return 1;
  }

  size_t alphabet_length = 0;

  uint8_t* symbol_by_bytes = malloc(SYMBOL_BY_BYTES_LENGTH);
  if (symbol_by_bytes == NULL) {
    PRINTF_ERROR("failed to allocate memory for symbol by bytes, size: %u", SYMBOL_BY_BYTES_LENGTH);

    free(alphabet);

    return 2;
  }

  for (size_t index = 0; index < SYMBOL_BY_BYTES_LENGTH; index++) {
    symbol_by_bytes[index] = UNDEFINED_SYMBOL;
  }

  for (size_t index = 0; index < constants_length; index++) {
    const char* constant = constants[index];

    for (size_t jndex = 0; jndex < strlen(constant); jndex++) {
      uint8_t byte = constant[jndex];

      if (!has_symbol_for_byte(symbol_by_bytes, byte)) {
        add_symbol(alphabet, symbol_by_bytes, &alphabet_length, byte);

        if (is_alphabet_full(alphabet_length)) {
          // We don't need other symbols, alphabet is already full.
          break;
        }
      }
    }

    if (is_alphabet_full(alphabet_length)) {
      // We don't need other constants, alphabet is already full.
      break;
    }
  }

  *alphabet_ptr        = alphabet;
  *alphabet_length_ptr = alphabet_length;
  *symbol_by_bytes_ptr = symbol_by_bytes;

  return 0;
}

void print_alphabet_length(size_t alphabet_length)
{
  PRINT_LENGTH(alphabet_length);
  PRINT_GLUE();
}

#define SYMBOL_BY_BYTE_TEMPLATE "[%u] = %u"

void print_symbol_by_bytes(const uint8_t* alphabet, size_t alphabet_length, const uint8_t* symbol_by_bytes)
{
  INITIALIZE_SPACERS(true);

  for (size_t index = 0; index < alphabet_length; index++) {
    uint8_t byte = alphabet[index];

    PRINT_SPACER();
    PRINTF(SYMBOL_BY_BYTE_TEMPLATE, byte, symbol_by_bytes[byte])
  }

  PRINT_GLUE();
}
