set (CURRENT_LIST_DIR ${CMAKE_CURRENT_LIST_DIR})

function (generate_constants_from_registry NAME REGISTRY_DECLARATION_PATH CONSTANTS_DECLARATION_PATH)
  string (TOLOWER ${NAME} NAME_LOWER_CASE)
  set (NAME_LOWER_CASE ${NAME_LOWER_CASE} PARENT_SCOPE)

  set (MESSAGE_PREFIX "${NAME_LOWER_CASE} constants from registry")

  set (OUTPUT_CONSTANTS "CMAKE_CONSTANTS")

  set (NAME "cmake_generator_constants_from_registry")
  set (SOURCE_DIR "${CURRENT_LIST_DIR}/constants_from_registry")
  set (BINARY_DIR "${PROJECT_BINARY_DIR}/generator_constants_from_registry")

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
        COMMAND "${BINARY_DIR}/main" ${ARGN}
        RESULT_VARIABLE RUN_RESULT
        OUTPUT_VARIABLE RUN_OUTPUT
        ERROR_VARIABLE RUN_ERRORS
      )

      if (RUN_RESULT EQUAL 0)
        set (${OUTPUT_CONSTANTS} ${RUN_OUTPUT} PARENT_SCOPE)
        message (STATUS "${MESSAGE_PREFIX} - generated")

      else ()
        unset (${OUTPUT_CONSTANTS} PARENT_SCOPE)
        message (STATUS "${MESSAGE_PREFIX} - result: ${RUN_RESULT}, errors:\n${RUN_ERRORS}")
        message (STATUS "${MESSAGE_PREFIX} - failed to generate, using default")
      endif ()

    else ()
      unset (${OUTPUT_CONSTANTS} PARENT_SCOPE)
      message (STATUS "${MESSAGE_PREFIX} - compilation failed, using default")
    endif ()

    file (REMOVE_RECURSE ${BINARY_DIR})

  else ()
    unset (${OUTPUT_CONSTANTS} PARENT_SCOPE)
    message (STATUS "${MESSAGE_PREFIX} - LibXML2 is not working, using default")
  endif ()
endfunction ()
