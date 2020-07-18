cmake_minimum_required(VERSION 3.17)

doxygen_add_docs(docs 
  ${ftl_SOURCE_DIR}/include/ftl/ftl.hpp
  ${ftl_SOURCE_DIR}/include/ftl/iterator.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/mainpage.md
)
