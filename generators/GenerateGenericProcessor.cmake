set (CURRENT_LIST_DIR ${CMAKE_CURRENT_LIST_DIR})

function (generate_generic_processor NAME OPTIONS_PATH)
  string (TOLOWER ${NAME} NAME_LOWER_CASE)
  set (NAME_LOWER_CASE ${NAME_LOWER_CASE} PARENT_SCOPE)

  set (MESSAGE_PREFIX "${NAME_LOWER_CASE} generic processor")

  set (OUTPUT_MIN_LENGTH    "CMAKE_MIN_LENGTH")
  set (OUTPUT_MAX_LENGTH    "CMAKE_MAX_LENGTH")
  set (OUTPUT_ALLOWED_BYTES "CMAKE_ALLOWED_BYTES")

  set (NAME "cmake_generator_generic_processor")
  set (SOURCE_DIR "${CURRENT_LIST_DIR}/generic_processor")
  set (BINARY_DIR "${PROJECT_BINARY_DIR}/generator_generic_processor")

  include (GetVerboseFlags)
  cmake_get_verbose_flags ()

  include (CheckC11)
  cmake_check_c11 ()

  try_compile (
    COMPILE_RESULT ${BINARY_DIR} ${SOURCE_DIR} ${NAME}
    CMAKE_FLAGS
      "-DCMAKE_C_FLAGS=${CMAKE_VERBOSE_C_FLAGS} ${CMAKE_C11_C_FLAGS} ${CMAKE_WERROR_C_FLAGS}"
      "-DCMAKE_VERBOSE_MAKEFILE=${CMAKE_VERBOSE_MAKEFILE}"
    OUTPUT_VARIABLE COMPILE_OUTPUT
  )

  if (CMAKE_VERBOSE_MAKEFILE)
    message (STATUS ${COMPILE_OUTPUT})
  endif ()

  if (COMPILE_RESULT)
    execute_process (
      COMMAND "${BINARY_DIR}/main" ${OPTIONS_PATH}
      RESULT_VARIABLE RUN_RESULT
      OUTPUT_VARIABLE RUN_OUTPUT
      ERROR_VARIABLE RUN_ERRORS
    )

    if (RUN_RESULT EQUAL 0)
      list (GET RUN_OUTPUT 0 MIN_LENGTH)
      set (${OUTPUT_MIN_LENGTH} ${MIN_LENGTH} PARENT_SCOPE)
      list (GET RUN_OUTPUT 1 MAX_LENGTH)
      set (${OUTPUT_MAX_LENGTH} ${MAX_LENGTH} PARENT_SCOPE)
      list (GET RUN_OUTPUT 2 ALLOWED_BYTES)
      set (${OUTPUT_ALLOWED_BYTES} ${ALLOWED_BYTES} PARENT_SCOPE)
      message (STATUS "${MESSAGE_PREFIX} - generated")
    else ()
      unset (${OUTPUT_MIN_LENGTH} PARENT_SCOPE)
      unset (${OUTPUT_MAX_LENGTH} PARENT_SCOPE)
      unset (${OUTPUT_ALLOWED_BYTES} PARENT_SCOPE)
      message (STATUS "${MESSAGE_PREFIX} - result: ${RUN_RESULT}, errors:\n${RUN_ERRORS}")
      message (STATUS "${MESSAGE_PREFIX} - failed to generate, using default")
    endif ()
  else ()
    unset (${OUTPUT_MIN_LENGTH} PARENT_SCOPE)
    unset (${OUTPUT_MAX_LENGTH} PARENT_SCOPE)
    unset (${OUTPUT_ALLOWED_BYTES} PARENT_SCOPE)
    message (STATUS "${MESSAGE_PREFIX} - compilation failed, using default")
  endif ()
endfunction ()
