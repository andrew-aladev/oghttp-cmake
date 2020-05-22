cmake_minimum_required (VERSION 3.9)
project ("cmake_generate_constant_processor" "C")

set (CMAKE_TARGET_PATH "" CACHE STRING "target path")

include ("../toolchain.cmake")

include_directories (${CMAKE_CURRENT_SOURCE_DIR})

add_executable (
  "main"
  "${CMAKE_TARGET_PATH}/options.c"
  "data.c"
  "main.c"
  "max_state.c"
)
