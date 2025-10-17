add_executable(trade main.cpp)

find_package(OpenSSL REQUIRED)
if(OPENSSL_FOUND)
    # This defines CPPHTTPLIB_OPENSSL_SUPPORT for the compiler
    target_compile_definitions(trade PRIVATE CPPHTTPLIB_OPENSSL_SUPPORT)
    target_link_libraries(trade PRIVATE OpenSSL::SSL OpenSSL::Crypto)
endif()

target_compile_options(trade PRIVATE 
    -fopenmp
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


target_sources(trade PRIVATE
    main.cpp    
    networking/alpaca/services/account/account_service.cpp
    core/config/config.cpp
)
