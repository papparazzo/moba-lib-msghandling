cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

project(moba-lib-msghandling VERSION 0.1.0)

configure_file(config.h.in config.h)

include(GNUInstallDirs)
add_library(
    moba-lib-msghandling STATIC

    src/moba/endpoint.cpp 
    src/moba/socket.cpp 
    src/moba/timestruct.cpp 
)

install(TARGETS moba-lib-msghandling)

target_include_directories(moba-lib-msghandling PUBLIC "${PROJECT_BINARY_DIR}")
