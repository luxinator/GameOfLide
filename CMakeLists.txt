cmake_minimum_required(VERSION 3.2)
project(GameOfLide_SDL2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -g")

set(SOURCE_FILES main.cpp GameBoard.cpp)
add_executable(GameOfLide_SDL2 ${SOURCE_FILES})

find_package(PkgConfig REQUIRED)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})


target_link_libraries(GameOfLide_SDL2 ${SDL2_LIBRARIES})