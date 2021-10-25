cmake_minimum_required(VERSION 3.1)

project(MazeVisibility)
set(CMAKE_FIND_ROOT_PATH /c/MinGW/)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAEK_EXE_LINKER_FLAGS_INIT "-static-libgcc -static-libstdc++")
set(CMAKE_CREATE_WIN32_EXE  "/subsystem:windowsce -mwindows")

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src/)

add_Definitions("-D_XKEYCHECK_H")
add_definitions(-DPROJECT_DIR="${PROJECT_SOURCE_DIR}")

add_executable(MazeVisibility
    ${SRC_DIR}MapWidget.h
    ${SRC_DIR}MapWidget.cpp
    ${SRC_DIR}Maze.h
    ${SRC_DIR}Maze.cpp
    ${SRC_DIR}MazeWindow.h
    ${SRC_DIR}MazeWindow.cpp
    ${SRC_DIR}RunMaze.cpp
    )

add_library(Maze 
    ${SRC_DIR}Cell.h
    ${SRC_DIR}Cell.cpp
    ${SRC_DIR}Edge.h
    ${SRC_DIR}Edge.cpp
    ${SRC_DIR}LineSeg.h
    ${SRC_DIR}LineSeg.cpp
    ${SRC_DIR}Point.h
    ${SRC_DIR}Vertex.cpp
    ${SRC_DIR}Vertex.h
    )

add_library(Matrix
    ${SRC_DIR}Matrix.h
    ${SRC_DIR}Matrix.cpp
    )

add_executable(Test
    ${SRC_DIR}test.cpp
    )

target_link_libraries(MazeVisibility fltk fltk_forms fltk_images fltk_jpeg fltk_png fltk_gl crypt32 comctl32)
target_link_libraries(MazeVisibility opengl32 glew32 freeglut glu32)
target_link_libraries(MazeVisibility Maze Matrix)

target_link_libraries(Test Matrix)