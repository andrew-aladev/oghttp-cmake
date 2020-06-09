cmake_minimum_required (VERSION 3.9)
project ("cmake_generate_constant_processor" "C")

set (CMAKE_LIBXML2_INCLUDE_DIRS "" CACHE STRING "LibXML2 include directories")
set (CMAKE_LIBXML2_LIBRARIES    "" CACHE STRING "LibXML2 libraries")

set (PROCESSOR_PATH ${CMAKE_CURRENT_LIST_DIR})

configure_file ("../common/config.h.in" "${CMAKE_CURRENT_LIST_DIR}/config.h")

include ("../common/toolchain.cmake")

include_directories (
  "."
  "../common"
  ${CMAKE_LIBXML2_INCLUDE_DIRS}
)
add_executable (
  "main"
  "../common/options_schema.c"
  "data/bytes.c"
  "data/length.c"
  "data/main.c"
  "options/constant.c"
  "options/main.c"
  "main.c"
)
target_link_libraries (
  "main"
  ${CMAKE_LIBXML2_LIBRARIES}
)
