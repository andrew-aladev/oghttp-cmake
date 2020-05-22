cmake_minimum_required (VERSION 3.9)
project ("cmake_generate_constants_from_registry" "C")

set (CMAKE_LIBXML2_INCLUDE_DIRS "" CACHE STRING "XML2 include directories")
set (CMAKE_LIBXML2_LIBRARIES    "" CACHE STRING "XML2 libraries")

include ("../toolchain.cmake")

include_directories (${CMAKE_LIBXML2_INCLUDE_DIRS})

add_executable (
  "main"
  "constants.c"
  "files.c"
  "main.c"
)
target_link_libraries ("main" ${CMAKE_LIBXML2_LIBRARIES})
