cmake_minimum_required (VERSION 3.9)
project ("oghttp-cmake" "C")

if (PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message (FATAL_ERROR "In-source builds are not allowed")
endif ()

if (NOT DEFINED OGH_TARGET)
  set (OGH_TARGET ${PROJECT_NAME})
endif ()

option (OGH_SHARED   "build shared binaries" ON)
option (OGH_STATIC   "build static binaries" OFF)
option (OGH_TESTS    "build tests"           ON)
option (OGH_COVERAGE "enable coverage"       OFF)

if (NOT OGH_SHARED AND NOT OGH_STATIC)
  message (FATAL_ERROR "Please enable building of shared or static binaries.")
endif ()

set (
  CMAKE_MODULE_PATH
  "${PROJECT_SOURCE_DIR}/checks"
  "${PROJECT_SOURCE_DIR}/functions"
  "${PROJECT_SOURCE_DIR}/generators"
)

include (GetVerboseFlags)
cmake_get_verbose_flags ()

include (GetPipeFlags)
cmake_get_pipe_flags ()

if (OGH_COVERAGE)
  include (GetCoverageFlags)
  cmake_get_coverage_flags ()
endif ()

include (CheckC11)
cmake_check_c11 ()

include (CheckIPO)
cmake_check_ipo ()

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_VERBOSE_C_FLAGS} ${CMAKE_PIPE_C_FLAGS} ${CMAKE_C11_C_FLAGS}")

if (OGH_COVERAGE)
  set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_COVERAGE_C_FLAGS}")
endif ()

if (NOT DEFINED CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
  set (CMAKE_BUILD_TYPE "DEBUG")
endif ()

set (CMAKE_C_FLAGS_DEBUG         "-O0 -g" CACHE STRING "debug cflags"         FORCE)
set (CMAKE_C_FLAGS_RELEASE       "-O2"    CACHE STRING "release cflags"       FORCE)
set (CMAKE_C_FLAGS_RELEASE_EMBED "-Os"    CACHE STRING "release embed cflags" FORCE)

if (CMAKE_HAVE_IPO)
  set (CMAKE_INTERPROCEDURAL_OPTIMIZATION true CACHE BOOL "status of IPO")
else ()
  set (CMAKE_INTERPROCEDURAL_OPTIMIZATION false CACHE BOOL "status of IPO")
endif ()

if (OGH_TESTS)
  enable_testing ()
endif ()

add_subdirectory ("src")
