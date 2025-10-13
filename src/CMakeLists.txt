add_executable(trade main.cpp)

file(GLOB_RECURSE SOURCE_FILES
    "*.cpp"
    "core/*.cpp"
    "execution/*.cpp"
    "networking/*.cpp"
)

file(GLOB_RECURSE HEADER_FILES 
    "*.h"
    "core/*.h"
    "execution/*.h"
    "networking/*.h"
)

target_sources(trade PRIVATE ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(trade PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(trade PRIVATE 
    ib_api
)
