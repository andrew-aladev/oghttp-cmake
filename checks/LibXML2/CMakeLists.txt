cmake_minimum_required (VERSION 3.9)
project ("cmake_check_libxml2" "C")

set (CMAKE_LIBXML2_INCLUDE_DIRS "" CACHE STRING "XML2 include directories")
set (CMAKE_LIBXML2_LIBRARIES    "" CACHE STRING "XML2 libraries")

set (CMAKE_TRY_RUN false CACHE BOOL "try run targets after build")

include_directories (${CMAKE_LIBXML2_INCLUDE_DIRS})

add_executable ("main" "main.c")
target_link_libraries ("main" ${CMAKE_LIBXML2_LIBRARIES})

if (CMAKE_TRY_RUN)
  add_custom_command (
    TARGET "main"
    POST_BUILD
    COMMAND "./main"
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  )
endif ()
