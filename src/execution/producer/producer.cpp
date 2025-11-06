#include "producer.hpp"

void producer(int id, TCPServer &server, TaskPool &tp, std::atomic<bool> &connection) {
    while (connection.load()) {
        // Need to implement server 
        std::vector<uint8_t> stream = server.receive();  
        auto data = deserialize(stream); 
        // Check what type of data 
        //tp.addWork(data);
    }
}
