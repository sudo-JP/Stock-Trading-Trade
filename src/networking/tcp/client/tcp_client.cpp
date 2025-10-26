#include "tcp_client.h"
#include "string.h"
#include <iostream>

bool TCPClient::send_data(BinaryMessage msg) { 
    if (!socket.is_open()) return false; 

    AccountBinaryPayload abp;  
    strcpy(abp.account_id, "Hello"); 
    strcpy(abp.currency, "USD");
    abp.buying_power = 1;
    abp.cash = 1000;
    abp.portfolio_value = 20000; 
    abp.equity = 2; 
    abp.unrealized_pl = 5; 
    abp.realized_pl = 7; 
    abp.status = 1;
    abp.last_update = 999;

    msg.data_size = sizeof(AccountBinaryPayload);
    std::vector<uint8_t> message = serialize(msg, &abp, sizeof(AccountBinaryPayload)); 
    //std::string message = "Hello world!\n";

    boost::system::error_code ec;
std::cout << "Attempting to send: " << message.size() << " bytes" << std::endl;
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

