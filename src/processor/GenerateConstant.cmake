set (CURRENT_LIST_DIR ${CMAKE_CURRENT_LIST_DIR})

function (generate_constant NAME)
  set (GENERATOR_PATH "${CURRENT_LIST_DIR}/constant")
  set (TARGET_PATH ${CMAKE_CURRENT_SOURCE_DIR})

  include (GenerateConstantProcessor)
  generate_constant_processor (${NAME} ${TARGET_PATH})

  if (DEFINED CMAKE_CONSTANT_BYTES)
    file (RELATIVE_PATH RELATIVE_SOURCE_PATH ${TARGET_PATH} ${SOURCE_PATH})

    configure_file ("${GENERATOR_PATH}/main.h.in" "${TARGET_PATH}/main.h")
    configure_file ("${GENERATOR_PATH}/main.c.in" "${TARGET_PATH}/main.c")
  endif ()
endfunction ()
