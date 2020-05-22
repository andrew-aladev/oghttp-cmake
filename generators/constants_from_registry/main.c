// Cmake tools for old generation HTTP (v0.9, v1.0, v1.1) C library.
// Copyright (c) 2019 AUTHORS, MIT License.

#include <stdlib.h>

#include "files.h"
#include "print.h"

int main(int argc, const char** argv)
{
  if (argc <= 1 || (argc - 1) % 2 != 0) {
    PRINT_ERROR("required arguments: groups of file path and xpath");
    return 1;
  }

  const char** file_datas        = argv + 1;
  size_t       file_datas_length = argc - 1;

  int result = process_files(file_datas, file_datas_length);
  if (result != 0) {
    return 2;
  }

  return 0;
}
