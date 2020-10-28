cmake_minimum_required(VERSION 3.18.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(NAME utext)
set(SOURCE_EXE main.cpp)

project(${NAME})

add_compile_options(
    -Wall
    -Wextra
    -Werror
    -Wpedantic
)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

include_directories(
    ./src
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../)

add_executable(${NAME} ${SOURCE_EXE})
add_subdirectory(src)

target_link_libraries(${NAME} Qt5::Core Qt5::Widgets app)
