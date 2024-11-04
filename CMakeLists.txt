cmake_minimum_required(VERSION 3.10)
project(MLM)

# build dir
set(CMAKE_BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)

# subdirectories
add_subdirectory(lib/UI)

#C# project
add_custom_target(MLM ALL
    COMMAND dotnet build -o ${CMAKE_BUILD_DIR}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS WM
)