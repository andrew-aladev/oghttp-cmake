cmake_minimum_required (VERSION 3.9)
project ("cmake_generate_constants_processor" "C")

set (CMAKE_TARGET_PATH "" CACHE STRING "target path")

include ("../toolchain.cmake")

include_directories (${CMAKE_CURRENT_SOURCE_DIR})

add_executable (
  "main"
  "${CMAKE_TARGET_PATH}/options.c"
  "alphabet.c"
  "data.c"
  "main.c"
  "max_state.c"
  "min_state_bits.c"
  "next_state_by_last_symbols.c"
  "prefix.c"
)
