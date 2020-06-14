set (CURRENT_LIST_DIR ${CMAKE_CURRENT_LIST_DIR})

function (generate_constant_processor NAME OPTIONS_PATH)
  string (TOLOWER ${NAME} NAME_LOWER_CASE)
  set (NAME_LOWER_CASE ${NAME_LOWER_CASE} PARENT_SCOPE)

  set (MESSAGE_PREFIX "${NAME_LOWER_CASE} constant processor")

  set (OUTPUT_CONSTANT_LENGTH "CMAKE_CONSTANT_LENGTH")
  set (OUTPUT_CONSTANT_BYTES  "CMAKE_CONSTANT_BYTES")

  set (NAME "cmake_generator_constant_processor")
  set (SOURCE_DIR "${CURRENT_LIST_DIR}/constant_processor")
  set (BINARY_DIR "${PROJECT_BINARY_DIR}/generator_constant_processor")

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
        "-DCMAKE_GENERATOR_USE_CURRENT_TOOLCHAIN=${CMAKE_GENERATOR_USE_CURRENT_TOOLCHAIN}"
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
        list (GET RUN_OUTPUT 0 CONSTANT_LENGTH)
        set (${OUTPUT_CONSTANT_LENGTH} ${CONSTANT_LENGTH} PARENT_SCOPE)
        list (GET RUN_OUTPUT 1 CONSTANT_BYTES)
        set (${OUTPUT_CONSTANT_BYTES} ${CONSTANT_BYTES} PARENT_SCOPE)
        message (STATUS "${MESSAGE_PREFIX} - generated")
      else ()
        unset (${OUTPUT_CONSTANT_LENGTH} PARENT_SCOPE)
        unset (${OUTPUT_CONSTANT_BYTES} PARENT_SCOPE)
        message (STATUS "${MESSAGE_PREFIX} - result: ${RUN_RESULT}, errors:\n${RUN_ERRORS}")
        message (STATUS "${MESSAGE_PREFIX} - failed to generate, using default")
      endif ()
    else ()
      unset (${OUTPUT_CONSTANT_LENGTH} PARENT_SCOPE)
      unset (${OUTPUT_CONSTANT_BYTES} PARENT_SCOPE)
      message (STATUS "${MESSAGE_PREFIX} - compilation failed, using default")
    endif ()

  else ()
    unset (${OUTPUT_CONSTANT_LENGTH} PARENT_SCOPE)
    unset (${OUTPUT_CONSTANT_BYTES} PARENT_SCOPE)
    message (STATUS "${MESSAGE_PREFIX} - LibXML2 is not working, using default")
  endif ()
endfunction ()
