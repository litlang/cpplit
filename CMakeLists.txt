cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(lit)

# source
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

# tokens
add_library(${PROJECT_NAME}_tokens INTERFACE)
target_include_directories(${PROJECT_NAME}_tokens INTERFACE "${SOURCE_DIR}/tokens/include")

## file reader
file(GLOB_RECURSE READER_SOURCES "${SOURCE_DIR}/reader/*.cpp")
add_library(${PROJECT_NAME}_reader STATIC ${READER_SOURCES})
target_include_directories(${PROJECT_NAME}_reader PRIVATE include)
target_include_directories(${PROJECT_NAME}_reader PRIVATE deps/codec/include)#..
target_include_directories(${PROJECT_NAME}_reader INTERFACE ${SOURCE_DIR}/reader/interface)

## scanner
file(GLOB_RECURSE SCANNER_SOURCES "${SOURCE_DIR}/scanner/*.cpp")
list(FILTER SCANNER_SOURCES EXCLUDE REGEX ".*old\\.cpp$")

add_library(${PROJECT_NAME}_scanner STATIC ${SCANNER_SOURCES})
target_include_directories(${PROJECT_NAME}_scanner PRIVATE include)
target_include_directories(${PROJECT_NAME}_scanner PRIVATE deps/codec/include)
target_link_libraries(${PROJECT_NAME}_scanner PRIVATE ${PROJECT_NAME}_tokens)

target_include_directories(${PROJECT_NAME}_scanner INTERFACE ${SOURCE_DIR}/scanner/interface)
target_include_directories(${PROJECT_NAME}_scanner PRIVATE ${SOURCE_DIR}/scanner/include)
target_link_libraries(${PROJECT_NAME}_scanner PRIVATE ${PROJECT_NAME}_reader)

## parser
file(GLOB_RECURSE PARSER_SOURCES "${SOURCE_DIR}/parser/*.cpp")
list(FILTER PARSER_SOURCES EXCLUDE REGEX ".*old\\.cpp$")

add_library(${PROJECT_NAME}_parser STATIC ${PARSER_SOURCES})
target_include_directories(${PROJECT_NAME}_parser PRIVATE include)
target_include_directories(${PROJECT_NAME}_parser PRIVATE deps/codec/include)
target_include_directories(${PROJECT_NAME}_parser INTERFACE ${SOURCE_DIR}/parser/interface)
target_include_directories(${PROJECT_NAME}_parser PRIVATE ${SOURCE_DIR}/parser/include)
target_link_libraries(${PROJECT_NAME}_parser PRIVATE ${PROJECT_NAME}_tokens)
target_link_libraries(${PROJECT_NAME}_parser PRIVATE ${PROJECT_NAME}_scanner)

## other
file(GLOB_RECURSE AST_SOURCES "${SOURCE_DIR}/ast/*.cpp")
list(FILTER AST_SOURCES EXCLUDE REGEX ".*old\\.cpp$")

file(GLOB_RECURSE SEMANTIC_SOURCES "${SOURCE_DIR}/semantic/*.cpp")
list(FILTER SEMANTIC_SOURCES EXCLUDE REGEX ".*old\\.cpp$")

file(GLOB_RECURSE UTILS_SOURCES "${SOURCE_DIR}/utils/*.cpp")
list(FILTER UTILS_SOURCES EXCLUDE REGEX ".*old\\.cpp$")

file(GLOB_RECURSE UI_SOURCES "${SOURCE_DIR}/ui/*.cpp")
list(FILTER UI_SOURCES EXCLUDE REGEX ".*old\\.cpp$")

add_executable(${PROJECT_NAME} ${AST_SOURCES} ${SEMANTIC_SOURCES} ${UTILS_SOURCES} ${UI_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE "include")
target_include_directories(${PROJECT_NAME} PRIVATE "${SOURCE_DIR}/ui/include")
target_include_directories(${PROJECT_NAME} PRIVATE deps/codec/include)


# Dependencies
set(DEPS_DIR ${PROJECT_SOURCE_DIR}/deps) # set dependencies directory
set(CMAKE_FIND_LIBRARY_SUFFIXES ".a" ".so" ".lib" ".dll" ".dylib")

## GMP Library
set(GMP_DIR ${DEPS_DIR}/gmp)
include_directories(${GMP_DIR}/include)

find_library(GMP_LIBRARY gmp ${GMP_DIR}/lib) # no-default-path required
find_library(GMPXX_LIBRARY gmpxx ${GMP_DIR}/lib)

target_link_libraries(${PROJECT_NAME} ${GMPXX_LIBRARY} ${GMP_LIBRARY})

## Losh Library
set(LOSH_DIR ${DEPS_DIR}/losh)
target_include_directories(${PROJECT_NAME} PRIVATE ${LOSH_DIR}/include)

find_library(LOSH_LIBRARY NAMES losh PATHS ${LOSH_DIR}/lib NO_DEFAULT_PATH REQUIRED)

## codec Library
set(CODEC_DIR ${DEPS_DIR}/codec)
find_library(CODEC_LIBRARY NAMES codec PATHS ${CODEC_DIR}/lib NO_DEFAULT_PATH REQUIRED)
target_link_libraries(${PROJECT_NAME}_reader PUBLIC ${CODEC_LIBRARY}) # 资源会浪费吗？
# target_link_libraries(${PROJECT_NAME} ${CODEC_LIBRARY})


##..
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_scanner) #ui/main
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_parser)
target_link_libraries(${PROJECT_NAME} ${LOSH_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_tokens) #ast

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