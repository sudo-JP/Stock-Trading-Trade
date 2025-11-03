#include "networking/alpaca/services/account/account_service.h"
#include "core/config/config.h"
#include "networking/tcp/client/tcp_client.h"
#include <iostream>
#include <future>
#define PORT_RANGE 100
#define THREADS 100

int main() {
    // Handshake 
    ENV env = getEnv();
    AccountService ser(env); 
    std::cout << env.URL << std::endl;
    AccountBinaryPayload payload = ser.getAccount(true).get();
    std::cout << "ID: " << payload.account_id << std::endl;
    
    /*TCPClient client(env);
    BinaryMessage msg; 
    // Filler value 
    msg.sql_command = SQLCommand::INSERT;
    msg.table = SQLTable::ACCOUNT;
    msg.type = MessageType::HANDSHAKE;

    Handshake hs = { THREADS, PORT_RANGE }; 
    if (!client.send_data(msg, &hs, sizeof(Handshake))) {
        std::cerr << "Failed to handshake with other repos" << std::endl;
        return -1; 
    }


    // Closing handshake 
    msg.type = MessageType::SHUTDOWN; 
    Shutdown sd = { 0, 0 }; 
    if (!client.send_data(msg, &sd, sizeof(Shutdown))) {
        std::cerr << "Failed to close connection with other repos" << std::endl;
        return -1; 
    }
    client.disconnect();*/
    return 0;
}
