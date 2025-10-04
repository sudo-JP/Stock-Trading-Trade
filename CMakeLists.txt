cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project(stock-trading-trade LANGUAGES CXX)

# IB API setup
add_library(ib_api INTERFACE)
target_include_directories(ib_api INTERFACE
    ${CMAKE_SOURCE_DIR}/api/IBJts/source/cppclient/client
    ${CMAKE_SOURCE_DIR}/api/IBJts/source/cppclient/client/protobufUnix
)

# Link the Intel decimal library
target_link_libraries(ib_api INTERFACE
    ${CMAKE_SOURCE_DIR}/api/IBJts/source/cppclient/libbid.a
)
add_subdirectory(src)
