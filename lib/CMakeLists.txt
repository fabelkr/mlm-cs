cmake_minimum_required(VERSION 3.27)
project(lib)

set(CMAKE_CXX_STANDARD 14)

find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

add_definitions(-DSHADER_DIR="${CMAKE_CURRENT_SOURCE_DIR}/UI/Shaders/")
add_definitions(-DV_SHADER="${CMAKE_CURRENT_SOURCE_DIR}/UI/Shaders/Vertex.glsl")
add_definitions(-DF_SHADER="${CMAKE_CURRENT_SOURCE_DIR}/UI/Shaders/Fragment.glsl")

include_directories(UI)
include_directories(UI/Renderer)
include_directories(UI/Renderer/Model)
include_directories(UI/WindowManager)

add_executable(lib
        UI/Renderer/Model/ModelInterface.hpp
        UI/Renderer/Model/ModelManager.cpp
        UI/Renderer/Model/ModelManager.hpp
        UI/Renderer/Model/Rect.cpp
        UI/Renderer/Model/Rect.hpp
        UI/Renderer/Renderer.cpp
        UI/Renderer/Renderer.h
        UI/Renderer/Types.hpp
        UI/WindowManager/WM.cpp
        UI/WindowManager/WM.h
        UI/WindowManager/WMWrapper.cpp
        UI/Export.h
        test.cpp)

target_link_libraries(lib glfw GLEW::GLEW glm::glm)
