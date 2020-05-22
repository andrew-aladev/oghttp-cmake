function (generate_constant_processor PREFIX TARGET_PATH)
  string (TOLOWER ${PREFIX} PREFIX_LOWER_CASE)
  set (PREFIX_LOWER_CASE ${PREFIX_LOWER_CASE} PARENT_SCOPE)

  set (MESSAGE_PREFIX "${PREFIX_LOWER_CASE} constant processor")

  set (OUTPUT_CONSTANT_SYMBOLS "CMAKE_CONSTANT_SYMBOLS")
  set (OUTPUT_CONSTANT_LENGTH "CMAKE_CONSTANT_LENGTH")

  set (NAME "cmake_generate_constant_processor")
  set (BINARY_DIR "${PROJECT_BINARY_DIR}/CMakeTmp/generate_constant_processor")
  set (SOURCE_DIR "${PROJECT_SOURCE_DIR}/cmake/generators/constant_processor")

  include (GetVerboseFlags)
  cmake_get_verbose_flags ()

  include (CheckC11)
  cmake_check_c11 ()

  try_compile (
    COMPILE_RESULT ${BINARY_DIR} ${SOURCE_DIR} ${NAME}
    CMAKE_FLAGS
      "-DCMAKE_C_FLAGS=${CMAKE_VERBOSE_C_FLAGS} ${CMAKE_C11_C_FLAGS} ${CMAKE_WERROR_C_FLAGS}"
      "-DCMAKE_VERBOSE_MAKEFILE=${CMAKE_VERBOSE_MAKEFILE}"
      "-DCMAKE_TARGET_PATH=${TARGET_PATH}"
    OUTPUT_VARIABLE COMPILE_OUTPUT
  )

  if (CMAKE_VERBOSE_MAKEFILE)
    message (STATUS ${COMPILE_OUTPUT})
  endif ()

  if (COMPILE_RESULT)
    execute_process (
      COMMAND "${BINARY_DIR}/main"
      RESULT_VARIABLE RUN_RESULT
      OUTPUT_VARIABLE RUN_OUTPUT
      ERROR_VARIABLE RUN_ERRORS
    )

    if (RUN_RESULT EQUAL 0)
      list (GET RUN_OUTPUT 0 CONSTANT_SYMBOLS)
      set (${OUTPUT_CONSTANT_SYMBOLS} ${CONSTANT_SYMBOLS} PARENT_SCOPE)
      list (GET RUN_OUTPUT 1 CONSTANT_LENGTH)
      set (${OUTPUT_CONSTANT_LENGTH} ${CONSTANT_LENGTH} PARENT_SCOPE)
      message (STATUS "${MESSAGE_PREFIX} - generated")
    else ()
      unset (${OUTPUT_CONSTANT_SYMBOLS} PARENT_SCOPE)
      unset (${OUTPUT_CONSTANT_LENGTH} PARENT_SCOPE)
      message (STATUS "${MESSAGE_PREFIX} - result: ${RUN_RESULT}, errors:\n${RUN_ERRORS}")
      message (STATUS "${MESSAGE_PREFIX} - failed to generate, using default")
    endif ()
  else ()
    unset (${OUTPUT_CONSTANT_SYMBOLS} PARENT_SCOPE)
    unset (${OUTPUT_CONSTANT_LENGTH} PARENT_SCOPE)
    message (STATUS "${MESSAGE_PREFIX} - compilation failed, using default")
  endif ()

  file (REMOVE_RECURSE ${BINARY_DIR})
endfunction ()
