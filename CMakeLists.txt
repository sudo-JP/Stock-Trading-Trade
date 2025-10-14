cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project(trade LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

target_compile_options(trade PRIVATE 
    -O2
)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

target_include_directories(trade PRIVATE 
    ${CMAKE_SOURCE_DIR}/library
)

add_subdirectory(src)

