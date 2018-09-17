cmake_minimum_required(VERSION 3.12)
project(Project)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project main.cpp Headers/vertex.h Source/vertex.cpp Source/direction.cpp Headers/direction.h Source/colordbl.cpp Headers/colordbl.h Source/ray.cpp Headers/ray.h Source/triangle.cpp Headers/triangle.h Source/scene.cpp Headers/scene.h Source/pixel.cpp Headers/pixel.h Source/camera.cpp Headers/camera.h)