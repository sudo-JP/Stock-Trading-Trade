#include "tcp_client.h"
#include <iostream>

bool TCPClient::send_data(TCPMessage msg) {

}

bool TCPClient::disconnect() {
    if (!socket.is_open()) {
        std::cerr << "Can't close a closed socket" << std::endl;
        return false; 
    }
    boost::system::error_code ec; 
    auto temp = socket.shutdown(tcp::socket::shutdown_both, ec); 
    if (ec) {
        std::cerr << "Socket shutdown warning" << ec.message() <<std::endl;
    }
    socket.close();
    return true;
}

