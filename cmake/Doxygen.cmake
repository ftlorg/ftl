function(enable_doxygen)
  option(ENABLE_DOXYGEN "Enable doxygen doc builds of source" OFF)
  if(ENABLE_DOXYGEN)
    set(DOXYGEN_CALLER_GRAPH YES)
    set(DOXYGEN_CALL_GRAPH YES)
    set(DOXYGEN_EXTRACT_ALL YES)
    find_package(Doxygen REQUIRED dot)
    doxygen_add_docs(docs 
      ${mylib_SOURCE_DIR}/include/mylib/core.hpp
      ${mylib_SOURCE_DIR}/docs/mainpage.md
      WORKING_DIRECTORY 
      ${mylib_SOURCE_DIR}/include
    )
  endif()
endfunction()
