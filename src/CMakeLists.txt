add_executable(trade main.cpp)

target_compile_options(trade PRIVATE 
    -O2
)

target_include_directories(trade PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/networking/alpaca/models
    ${CMAKE_CURRENT_SOURCE_DIR}/networking/alpaca/services
)

target_sources(trade PRIVATE
    
)
