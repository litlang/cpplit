cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(lit VERSION 0.0.0)

# set distribution directory
set(DIST_DIR ${CMAKE_SOURCE_DIR}/dist)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${DIST_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${DIST_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${DIST_DIR}/lib)

set(CMAKE_FIND_LIBRARY_SUFFIXES ".a" ".so" ".lib" ".dll" ".dylib")
set(DEPS_DIR ${PROJECT_SOURCE_DIR}/deps)
set(GMP_DIR ${DEPS_DIR}/gmp)

file(GLOB_RECURSE READER_SOURCES "src/reader/*.cpp")
add_library(${PROJECT_NAME}_reader STATIC ${READER_SOURCES})
target_include_directories(${PROJECT_NAME}_reader INTERFACE src/reader/interface)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE OLD_SOURCES "src/*.old.cpp")
list(REMOVE_ITEM SOURCES ${OLD_SOURCES})
list(REMOVE_ITEM SOURCES src/reader/reader.cpp) #..

include_directories(${GMP_DIR}/include)
include_directories("include")

find_library(GMP_LIBRARY gmp ${GMP_DIR}/lib)
find_library(GMPXX_LIBRARY gmpxx ${GMP_DIR}/lib)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${GMPXX_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${GMP_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_reader)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-static" LINK_SEARCH_START_STATIC TRUE LINK_SEARCH_END_STATIC TRUE)
endif()

# set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

install(TARGETS ${PROJECT_NAME} DESTINATION bin) #..lib? install libs
add_custom_target(uninstall
  COMMAND xargs rm < install_manifest.txt
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Uninstalling...")