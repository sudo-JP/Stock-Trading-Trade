#include "consumer.hpp"


void consumer(int id, TCPClient &client, TaskPool &tp, std::atomic<bool> &connection) {
    std::vector<std::function<void()>> works; 
    while (connection.load()) {
        works = tp.getWork(); 
        for (auto work : works) {
            work();
        }
        BinaryMessage msg; 
        client.send_data(msg, (void *)true, 0);
    }
}
