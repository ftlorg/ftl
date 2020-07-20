cmake_minimum_required(VERSION 3.17)

add_library(ftl 
    ftl.cpp
    ${ftl_SOURCE_DIR}/include/ftl/array.hpp
    ${ftl_SOURCE_DIR}/include/ftl/ftl.hpp
    ${ftl_SOURCE_DIR}/include/ftl/into_iterator_trait.hpp
    ${ftl_SOURCE_DIR}/include/ftl/iterator_interface.hpp
    )

target_include_directories(ftl 
  PUBLIC
  $<BUILD_INTERFACE:${ftl_BINARY_DIR}/include/>
  $<BUILD_INTERFACE:${ftl_SOURCE_DIR}/include/>
  $<INSTALL_INTERFACE:include/>
)

target_link_libraries(ftl
  PRIVATE
    $<BUILD_INTERFACE:project_options>
    $<BUILD_INTERFACE:project_warnings>)

install(TARGETS ftl EXPORT ftlTargets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include)

install(EXPORT ftlTargets
  FILE ftlTargets.cmake
  NAMESPACE ftl::
  DESTINATION lib/cmake/ftl)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ftlConfigVersion.cmake
  VERSION ${ftl_VERSION}
  COMPATIBILITY SameMajorVersion)

install(
  FILES "ftlConfig.cmake" "ftlConfigVersion.cmake"
  DESTINATION lib/cmake/ftl)
