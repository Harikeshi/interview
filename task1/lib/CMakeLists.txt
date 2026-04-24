cmake_minimum_required(VERSION 3.14)
#-------------------------------------------------------------------------------
project(ContactsLib VERSION 1.0.0 LANGUAGES CXX)
#-------------------------------------------------------------------------------
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
#-------------------------------------------------------------------------------
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
#-------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
#-------------------------------------------------------------------------------
add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES} "src/Models/ContactListModel.cpp")
#-------------------------------------------------------------------------------
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

target_link_libraries(${PROJECT_NAME} PUBLIC
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)
#-------------------------------------------------------------------------------
target_include_directories(${PROJECT_NAME} PUBLIC "include")
#-------------------------------------------------------------------------------
option(BUILD_TESTS "build testing" OFF)
if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
message("BUILD TEST: ${BUILD_TESTS}")
#-------------------------------------------------------------------------------
