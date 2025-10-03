cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(stock-trading-trade LANGUAGES CXX)

add_subdirectory(src)

add_subdirectory(api/IBJts/source/cppclient/)

