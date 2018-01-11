cmake_minimum_required(VERSION 3.8)
project(IMACMAN3D)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp)

find_package(SDL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

## Directories
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})


SET(CMAKE_CXX_LINK_FLAGS "-framework OpenGL -framework GLUT")


add_executable(IMACMAN3D ${SOURCE_FILES})