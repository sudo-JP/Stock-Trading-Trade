add_executable(trade main.cpp)

find_package(OpenSSL REQUIRED)
if(OPENSSL_FOUND)
    # This defines CPPHTTPLIB_OPENSSL_SUPPORT for the compiler
    target_compile_definitions(trade PRIVATE CPPHTTPLIB_OPENSSL_SUPPORT)
    target_link_libraries(trade PRIVATE OpenSSL::SSL OpenSSL::Crypto)
endif()

target_compile_options(trade PRIVATE 
    -O2
)

target_include_directories(trade PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/core 
    ${CMAKE_CURRENT_SOURCE_DIR}/core/config
    ${CMAKE_CURRENT_SOURCE_DIR}/networking/alpaca/models
    ${CMAKE_CURRENT_SOURCE_DIR}/networking/alpaca/services/account
    ${CMAKE_SOURCE_DIR}/library
)


target_sources(trade PRIVATE
    main.cpp    
    networking/alpaca/services/account/account_service.cpp
    core/config/config.cpp
)
