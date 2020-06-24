function (generate_constants_from_registry_wrapper NAME)
  set (TARGET_PATH ${CMAKE_CURRENT_SOURCE_DIR})

  include (GenerateConstantsFromRegistry)
  generate_constants_from_registry (
    ${NAME}
    "${TARGET_PATH}/registry_declaration.xml"
    "${TARGET_PATH}/declaration.xml"
    ${ARGN}
  )
endfunction ()
