#include <boost/asio.hpp>
#include "protocol.h"
#ifndef _TCP_CLIENT_H
#define _TCP_CLIENT_H

using boost::asio::ip::tcp;


class TCPClient {
    public: 
        TCPClient(const std::string host, const std::string port) : host(host), port(port), 
        io_context(), resolver(io_context), socket(io_context) {
            boost::asio::connect(socket, resolver.resolve(host, port)); 
        };

        bool send_data(const TCPMessage msg); 

        bool disconnect(); 

    private: 
        const std::string host;
        const std::string port; 
        tcp::socket socket; 
        tcp::resolver resolver; 
        boost::asio::io_context io_context;
}; 

#endif
