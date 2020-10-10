// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include <assert.h>
#include <stdalign.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>

// clang-format off
#define log_format(x) _Generic((x), \
  bool: "%d", \
  char *: "%s", \
  float: "%f", \
  size_t: "%zu", \
  void *: "%p" \
)
// clang-format on

#define log(x) printf(log_format(x), x), putchar('\n');

typedef struct
{
  bool is_float;
  union
  {
    float number;
    char* string;
  };
} data_t;

const data_t data = {.is_float = true, .number = 1.5};

noreturn void func()
{
  log(alignof(double));
  log(u8"fit");
  log((void*) &data);
  log(data.is_float);
  log(data.number);

  static_assert(1 < 2, "1 < 2");

  exit(0);
}

int main()
{
  func();
}
