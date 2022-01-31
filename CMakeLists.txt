cmake_minimum_required(VERSION 3.21)
project(GameOfLife)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/utils/board/Board.cpp src/utils/board/Board.h src/utils/ui/WindowManager.cpp src/utils/ui/WindowManager.h src/utils/board/Patterns.cpp src/utils/board/Patterns.h)
add_executable(GameOfLife ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(GameOfLife sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
