cmake_minimum_required(VERSION 3.30)
project(BST_Project C)

set(CMAKE_C_STANDARD 23)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(BST_Project main.c
        src/BST.c
        src/BST.h)

target_link_libraries(BST_Project OpenGL::GL GLUT::GLUT m /usr/lib64/libGLU.so)
