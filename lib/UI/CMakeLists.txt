#UI library (c++) -> {wm.dll , gl.dll}
cmake_minimum_required(VERSION 3.10)
project(UIcppLib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(OUTDIR ${CMAKE_CURRENT_SOURCE_DIR}/../../build/lib)


# include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/WindowManager 
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer
)

set(WM_SOURCES
    WindowManager/WM.mm
    WindowManager/WMWrapper.cpp
    # Renderer/Renderer.cpp
    # Renderer/Model/ModelManager.cpp
    # Renderer/Model/Rect.cpp
)


add_library(WM SHARED ${WM_SOURCES})

target_link_libraries(WM 
    "-framework Metal"
    "-framework QuartzCore"
    "-framework Cocoa"
)

set_target_properties(WM PROPERTIES
    PUBLIC_HEADER "WM.h"
    RUNTIME_OUTPUT_DIRECTORY ${OUTDIR}/UI
)

add_definitions(-DSHADER_DIR="${CMAKE_CURRENT_SOURCE_DIR}/Shaders/")

# Add compiler flags for Clang/GCC
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(WM PRIVATE -fdeclspec)
endif()