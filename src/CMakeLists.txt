add_executable(trade main.cpp)

find_package(OpenSSL REQUIRED)
if(OPENSSL_FOUND)
    # This defines CPPHTTPLIB_OPENSSL_SUPPORT for the compiler
    target_compile_definitions(trade PRIVATE CPPHTTPLIB_OPENSSL_SUPPORT)
    target_link_libraries(trade PRIVATE OpenSSL::SSL OpenSSL::Crypto)
endif()

find_package(Boost 1.70.0 REQUIRED COMPONENTS system)
target_link_libraries(trade PRIVATE Boost::system)

target_compile_options(trade PRIVATE 
    -O2
)

target_include_directories(trade PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}

    # Configs and types 
    ${CMAKE_CURRENT_SOURCE_DIR}/core 
    ${CMAKE_CURRENT_SOURCE_DIR}/core/config

    # Alpaca 
    ${CMAKE_CURRENT_SOURCE_DIR}/networking/alpaca/models
    ${CMAKE_CURRENT_SOURCE_DIR}/networking/alpaca/services/account

    # TCP 
    ${CMAKE_CURRENT_SOURCE_DIR}/networking/tcp/client
    ${CMAKE_CURRENT_SOURCE_DIR}/networking/tcp/common
    ${CMAKE_CURRENT_SOURCE_DIR}/networking/tcp/server

    ${CMAKE_SOURCE_DIR}/library
)

set(SERVICES "${CMAKE_CURRENT_SOURCE_DIR}/networking/alpaca/services")
set(TCP "${CMAKE_CURRENT_SOURCE_DIR}/networking/tcp")

target_sources(trade PRIVATE
    # Alpaca Services
    ${SERVICES}/account/account_service.cpp
    ${SERVICES}/asset/asset_service.cpp
    ${SERVICES}/order/order_service.cpp
    ${SERVICES}/position/position_service.cpp

    # TCP 
    ${TCP}/client/tcp_client.cpp

    # Config 
    core/config/config.cpp
)
