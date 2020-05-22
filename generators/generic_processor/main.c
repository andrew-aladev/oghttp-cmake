// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include "alphabet.h"
#include "data.h"
#include "max_state.h"

int main()
{
  print_data();

  // -- alphabet --

  print_allowed_bytes();

  // -- max state --

  int result = check_max_state();
  if (result != 0) {
    return 1;
  }

  return 0;
}
