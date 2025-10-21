add_executable(trade main.cpp)

set_target_properties(trade PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES)

find_package(OpenSSL REQUIRED)
target_compile_definitions(trade PRIVATE CPPHTTPLIB_OPENSSL_SUPPORT)
target_link_libraries(trade PRIVATE OpenSSL::SSL OpenSSL::Crypto)

find_package(Boost 1.70.0 REQUIRED COMPONENTS system)
target_link_libraries(trade PRIVATE Boost::system)

target_compile_options(trade PRIVATE 
    -Wall -Wextra -Wpedantic
    -g
    -O2
)

target_include_directories(trade PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/library
)

set(SERVICES "${CMAKE_CURRENT_SOURCE_DIR}/networking/alpaca/services")
set(TCP "${CMAKE_CURRENT_SOURCE_DIR}/networking/tcp")

# Alpaca Services
add_library(alpaca_services
    ${SERVICES}/account/account_service.cpp
    ${SERVICES}/asset/asset_service.cpp
    ${SERVICES}/order/order_service.cpp
    ${SERVICES}/position/position_service.cpp
)

# TCP 
add_library(tcp_client
    ${TCP}/client/tcp_client.cpp
)

target_link_libraries(trade PRIVATE alpaca_services tcp_client)

target_sources(trade PRIVATE
    core/config/config.cpp
)
