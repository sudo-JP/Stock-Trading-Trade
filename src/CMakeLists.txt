add_executable(trade main.cpp)

#file(GLOB NETWORK_SOURCES "network/ib_api/*.cpp")
#add_library(network STATIC ${NETWORK_SOURCES})
#target_include_directories(network PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/network)
#
#target_include_directories(trade PRIVATE
#${CMAKE_CURRENT_SOURCE_DIR} 
#)

target_link_libraries(trade PRIVATE 
    #network
    ib_api
)
