cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
set(CMAKE_BUILD_TYPE DEBUG)

# Meta information about the project
set(META_PROJECT_NAME        "stasis")
set(META_PROJECT_DESCRIPTION "A game about love")
set(META_AUTHOR_ORGANIZATION "Danulo")
set(META_AUTHOR_DOMAIN       "https://github.com/faitdivers/stasis")
set(META_AUTHOR_MAINTAINER   "jpedro.e.silva@gmail.com")
set(META_VERSION_MAJOR       "0")
set(META_VERSION_MINOR       "0")
set(META_VERSION_PATCH       "0")
set(META_VERSION             "${META_VERSION_MAJOR}.${META_VERSION_MINOR}.${META_VERSION_PATCH}")
set(META_NAME_VERSION        "${META_PROJECT_NAME} v${META_VERSION} (${META_VERSION_REVISION})")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(${META_PROJECT_NAME} C CXX)
set(SOURCE_DIR src)
set(INCLUDE_DIR inc)

add_definitions(-std=c++11)

# Aggregate the source files for building the main executable
file(GLOB PROJECT_SOURCES "${SOURCE_DIR}/*.cpp")

# Create main executable
include_directories(${INCLUDE_DIR})
add_executable(stasis ${PROJECT_SOURCES})
target_link_libraries (${META_PROJECT_NAME} ${SMFL_LIBRARIES})

# Find SMFL dependency
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
message("${CMAKE_MODULE_PATH}")
find_package(SFML 1.6 REQUIRED system window graphics network audio)
target_link_libraries(${META_PROJECT_NAME} ${SFML_LIBRARIES})
