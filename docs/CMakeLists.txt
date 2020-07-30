cmake_minimum_required(VERSION 3.17)

file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${ftl_SOURCE_DIR}/include/ftl/*.hpp")

doxygen_add_docs(docs 
  ${HEADER_LIST}
  ${CMAKE_CURRENT_SOURCE_DIR}/mainpage.md
)
