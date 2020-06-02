set (CURRENT_LIST_DIR ${CMAKE_CURRENT_LIST_DIR})

function (generate_constants_processor NAME OPTIONS_PATH)
  string (TOLOWER ${NAME} NAME_LOWER_CASE)
  set (NAME_LOWER_CASE ${NAME_LOWER_CASE} PARENT_SCOPE)

  set (MESSAGE_PREFIX "${NAME_LOWER_CASE} constants processor")

  set (OUTPUT_CONSTANTS_LENGTH           "CMAKE_CONSTANTS_LENGTH")
  set (OUTPUT_ALPHABET_LENGTH            "CMAKE_ALPHABET_LENGTH")
  set (OUTPUT_SYMBOL_BY_BYTES            "CMAKE_SYMBOL_BY_BYTES")
  set (OUTPUT_MAX_STATE                  "CMAKE_MAX_STATE")
  set (OUTPUT_MIN_STATE_BITS             "CMAKE_MIN_STATE_BITS")
  set (OUTPUT_NEXT_STATE_BY_LAST_SYMBOLS "CMAKE_NEXT_STATE_BY_LAST_SYMBOLS")

  set (NAME "cmake_generator_constants_processor")
  set (SOURCE_DIR "${CURRENT_LIST_DIR}/constants_processor")
  set (BINARY_DIR "${PROJECT_BINARY_DIR}/generator_constants_processor")

  find_package (LibXml2)

  include (CheckLibXML2)
  cmake_check_libxml2 ()

  if (CMAKE_LIBXML2_WORKS)
    include (GetVerboseFlags)
    cmake_get_verbose_flags ()

    include (CheckC11)
    cmake_check_c11 ()

    try_compile (
      COMPILE_RESULT ${BINARY_DIR} ${SOURCE_DIR} ${NAME}
      CMAKE_FLAGS
        "-DCMAKE_C_FLAGS=${CMAKE_VERBOSE_C_FLAGS} ${CMAKE_C11_C_FLAGS} ${CMAKE_WERROR_C_FLAGS}"
        "-DCMAKE_VERBOSE_MAKEFILE=${CMAKE_VERBOSE_MAKEFILE}"
        "-DCMAKE_LIBXML2_INCLUDE_DIRS=${LIBXML2_INCLUDE_DIRS}"
        "-DCMAKE_LIBXML2_LIBRARIES=${LIBXML2_LIBRARIES}"
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
        list (GET RUN_OUTPUT 0 CONSTANTS_LENGTH)
        set (${OUTPUT_CONSTANTS_LENGTH} ${CONSTANTS_LENGTH} PARENT_SCOPE)
        list (GET RUN_OUTPUT 1 ALPHABET_LENGTH)
        set (${OUTPUT_ALPHABET_LENGTH} ${ALPHABET_LENGTH} PARENT_SCOPE)
        list (GET RUN_OUTPUT 2 SYMBOL_BY_BYTES)
        set (${OUTPUT_SYMBOL_BY_BYTES} ${SYMBOL_BY_BYTES} PARENT_SCOPE)
        list (GET RUN_OUTPUT 3 MAX_STATE)
        set (${OUTPUT_MAX_STATE} ${MAX_STATE} PARENT_SCOPE)
        list (GET RUN_OUTPUT 4 MIN_STATE_BITS)
        set (${OUTPUT_MIN_STATE_BITS} ${MIN_STATE_BITS} PARENT_SCOPE)
        list (GET RUN_OUTPUT 5 NEXT_STATE_BY_LAST_SYMBOLS)
        set (${OUTPUT_NEXT_STATE_BY_LAST_SYMBOLS} ${NEXT_STATE_BY_LAST_SYMBOLS} PARENT_SCOPE)
        message (STATUS "${MESSAGE_PREFIX} - generated")
      else ()
        unset (${OUTPUT_CONSTANTS_LENGTH} PARENT_SCOPE)
        unset (${OUTPUT_ALPHABET_LENGTH} PARENT_SCOPE)
        unset (${OUTPUT_SYMBOL_BY_BYTES} PARENT_SCOPE)
        unset (${OUTPUT_MAX_STATE} PARENT_SCOPE)
        unset (${OUTPUT_MIN_STATE_BITS} PARENT_SCOPE)
        unset (${OUTPUT_NEXT_STATE_BY_LAST_SYMBOLS} PARENT_SCOPE)
        message (STATUS "${MESSAGE_PREFIX} - result: ${RUN_RESULT}, errors:\n${RUN_ERRORS}")
        message (STATUS "${MESSAGE_PREFIX} - failed to generate, using default")
      endif ()
    else ()
      unset (${OUTPUT_CONSTANTS_LENGTH} PARENT_SCOPE)
      unset (${OUTPUT_ALPHABET_LENGTH} PARENT_SCOPE)
      unset (${OUTPUT_SYMBOL_BY_BYTES} PARENT_SCOPE)
      unset (${OUTPUT_MAX_STATE} PARENT_SCOPE)
      unset (${OUTPUT_MIN_STATE_BITS} PARENT_SCOPE)
      unset (${OUTPUT_NEXT_STATE_BY_LAST_SYMBOLS} PARENT_SCOPE)
      message (STATUS "${MESSAGE_PREFIX} - compilation failed, using default")
    endif ()

  else ()
    unset (${OUTPUT_CONSTANTS_LENGTH} PARENT_SCOPE)
    unset (${OUTPUT_ALPHABET_LENGTH} PARENT_SCOPE)
    unset (${OUTPUT_SYMBOL_BY_BYTES} PARENT_SCOPE)
    unset (${OUTPUT_MAX_STATE} PARENT_SCOPE)
    unset (${OUTPUT_MIN_STATE_BITS} PARENT_SCOPE)
    unset (${OUTPUT_NEXT_STATE_BY_LAST_SYMBOLS} PARENT_SCOPE)
    message (STATUS "${MESSAGE_PREFIX} - LibXML2 is not working, using default")
  endif ()
endfunction ()
