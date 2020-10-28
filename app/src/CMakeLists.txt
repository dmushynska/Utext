cmake_minimum_required(VERSION 3.18.2)

set(NAME app)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
file(GLOB SOURCE *.cpp *.h *.ui)

add_library(${NAME} STATIC ${SOURCE})
target_link_libraries(${NAME} Qt5::Core Qt5::Widgets)
