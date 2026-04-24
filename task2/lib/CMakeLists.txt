cmake_minimum_required(VERSION 3.14)
#-------------------------------------------------------------------------------
project(ThreadsLib VERSION 1.0.0 LANGUAGES CXX)
#-------------------------------------------------------------------------------
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
#-------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
#-------------------------------------------------------------------------------
add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})
#-------------------------------------------------------------------------------
target_include_directories(${PROJECT_NAME} PUBLIC "include")
#-------------------------------------------------------------------------------
option(BUILD_THREADS_TESTS "build testing" OFF)
if(BUILD_THREADS_TESTS)
    add_subdirectory(tests)
endif()
message("BUILD THREADS TEST: ${BUILD_THREADS_TESTS}")
#-------------------------------------------------------------------------------