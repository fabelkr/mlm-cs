#UI library (c++) -> {wm.dll , gl.dll}
cmake_minimum_required(VERSION 3.10)
project(UIcppLib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# packages
# find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

set(OUTDIR ${CMAKE_CURRENT_SOURCE_DIR}/../../build/lib)

# add Zig exe (ShaderLoader)
# add_custom_command(
#     OUTPUT ${OUTDIR}/libShaderLoader.dylib
#     COMMAND zig build-lib ${CMAKE_CURRENT_SOURCE_DIR}/ShaderLoader.zig -dynamic -fPIC -femit-bin=${OUTDIR}/libShaderLoader.dylib
#     DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/ShaderLoader.zig
#     COMMENT "Building ShaderLoader Zig Library"
# )

# add_custom_target(ComptimeSL ALL DEPENDS ${OUTDIR}/libShaderLoader.dylib)
# include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/WindowManager 
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer
)

set(WM_SOURCES
    WindowManager/WM.cpp
    WindowManager/WMWrapper.cpp
    Renderer/Renderer.cpp
    Renderer/Model/ModelManager.cpp
    Renderer/Model/Rect.cpp
)


add_library(WM SHARED ${WM_SOURCES})

# add_dependencies(WM ComptimeSL)

target_link_libraries(WM 
    glfw GLEW::GLEW glm::glm 
    # ${OUTDIR}/libShaderLoader.dylib
)

set_target_properties(WM PROPERTIES
    PUBLIC_HEADER "WM.h"
    RUNTIME_OUTPUT_DIRECTORY ${OUTDIR}/UI
)

add_definitions(-DSHADER_DIR="${CMAKE_CURRENT_SOURCE_DIR}/Shaders/")
add_definitions(-DV_SHADER="${CMAKE_CURRENT_SOURCE_DIR}/Shaders/Vertex.glsl")
add_definitions(-DF_SHADER="${CMAKE_CURRENT_SOURCE_DIR}/Shaders/Fragment.glsl")

# Add compiler flags for Clang/GCC
# if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STRENGTH "GNU")
    target_compile_options(WM PRIVATE -fdeclspec)
    # target_compile_options(gl PRIVATE -fdeclspec)
# endif()