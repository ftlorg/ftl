cmake_minimum_required(VERSION 3.17)

add_executable(sandbox
  main.cpp
  application.cpp)

target_include_directories(sandbox
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/../include/
)

target_link_libraries(sandbox PRIVATE project_options project_warnings ftl)
