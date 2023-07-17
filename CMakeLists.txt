cmake_minimum_required(VERSION 3.20)

project(moba-lib-msghandling VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

configure_file(config.h.in config.h)

include(GNUInstallDirs)
add_library(
    moba-lib-msghandling 

    src/moba/endpoint.cpp 
    src/moba/socket.cpp 
    src/moba/timestruct.cpp 
)

install(TARGETS moba-lib-msghandling)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

target_include_directories(moba-lib-msghandling PUBLIC "${PROJECT_BINARY_DIR}")
