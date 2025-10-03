add_executable(trade main.cpp)

# Add all source directories
target_sources(trade PRIVATE
    core/types.cpp

)

# API 
target_include_directories(trade PRIVATE 
    $(CMAKE_SOURCE_DIR)/api/IBJts/source/cppclient
    $(CMAKE_CURRENT_SOURCE_DIR)
    $(CMAKE_CURRENT_SOURCE_DIR)/core
    $(CMAKE_CURRENT_SOURCE_DIR)/market_data
    $(CMAKE_CURRENT_SOURCE_DIR)/network 
)

target_link_libraries(trade PRIVATE ib_api)
