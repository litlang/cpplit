cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(lit)

# set distribution directory
set(DIST_DIR ${CMAKE_SOURCE_DIR}/dist)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${DIST_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${DIST_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${DIST_DIR}/lib)

set(CMAKE_FIND_LIBRARY_SUFFIXES ".a" ".so" ".lib" ".dll" ".dylib")
set(DEPS_DIR ${PROJECT_SOURCE_DIR}/deps)

# file reader
file(GLOB_RECURSE READER_SOURCES "src/reader/*.cpp")
add_library(${PROJECT_NAME}_reader STATIC ${READER_SOURCES})
target_include_directories(${PROJECT_NAME}_reader INTERFACE src/reader/interface)

# scanner
file(GLOB_RECURSE SCANNER_SOURCES "src/scanner/*.cpp")
file(GLOB_RECURSE OLD_SCANNER_SOURCES "src/*.old.cpp")
list(REMOVE_ITEM SCANNER_SOURCES ${OLD_SCANNER_SOURCES})

add_library(${PROJECT_NAME}_scanner STATIC ${SCANNER_SOURCES})
target_include_directories(${PROJECT_NAME}_scanner INTERFACE src/scanner/interface)
target_include_directories(${PROJECT_NAME}_scanner PRIVATE src/scanner/include)
target_link_libraries(${PROJECT_NAME}_scanner ${PROJECT_NAME}_reader)


# parser
file(GLOB_RECURSE PARSER_SOURCES src/parser/*.cpp)
file(GLOB_RECURSE OLD_PARSER_SOURCES src/parser/*.old.cpp)
list(REMOVE_ITEM PARSER_SOURCES ${OLD_PARSER_SOURCES})

add_library(${PROJECT_NAME}_parser STATIC ${PARSER_SOURCES})
target_include_directories(${PROJECT_NAME}_parser INTERFACE src/parser/interface)
target_include_directories(${PROJECT_NAME}_parser PRIVATE src/parser/include)
target_link_libraries(${PROJECT_NAME}_parser ${PROJECT_NAME}_scanner)


file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE OLD_SOURCES "src/*.old.cpp")
list(REMOVE_ITEM SOURCES ${OLD_SOURCES})
list(REMOVE_ITEM SOURCES ${READER_SOURCES} ${SCANNER_SOURCES} ${PARSER_SOURCES}) #..
add_executable(${PROJECT_NAME} ${SOURCES})

include_directories("include")

# GMP Library
set(GMP_DIR ${DEPS_DIR}/gmp)
include_directories(${GMP_DIR}/include)

find_library(GMP_LIBRARY gmp ${GMP_DIR}/lib)
find_library(GMPXX_LIBRARY gmpxx ${GMP_DIR}/lib)

target_link_libraries(${PROJECT_NAME} ${GMPXX_LIBRARY} ${GMP_LIBRARY})

# Losh Library
set(LOSH_DIR ${DEPS_DIR}/losh)
include_directories(${LOSH_DIR}/include)

find_library(LOSH_LIBRARY NAMES losh PATHS ${LOSH_DIR}/lib NO_DEFAULT_PATH REQUIRED)
target_link_libraries(${PROJECT_NAME} ${LOSH_LIBRARY})

target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_parser)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-static" LINK_SEARCH_START_STATIC TRUE LINK_SEARCH_END_STATIC TRUE)
endif()

install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)

add_custom_target(uninstall
  COMMAND xargs rm < install_manifest.txt
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Uninstalling...")