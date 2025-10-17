#include "tcp_client.h"
#include <iostream>

bool TCPClient::send_data(TCPMessage msg) {
    if (!socket.is_open()) return false; 

    std::string message = serialize(msg); 

    boost::system::error_code ec;
    boost::asio::write(socket, boost::asio::buffer(message), ec);

    if (ec) {
        std::cerr << "Send failed: " << ec.message() << std::endl;
        return false;
    } 

    return true; 
}

bool TCPClient::disconnect() {
    if (!socket.is_open()) {
        std::cerr << "Can't close a closed socket" << std::endl;
        return false; 
    }
    boost::system::error_code ec; 
    auto temp = socket.shutdown(tcp::socket::shutdown_both, ec); 
    if (ec) {
        std::cerr << "Socket shutdown warning: " << ec.message() << std::endl;
    }
    socket.close();
    return true;
}

