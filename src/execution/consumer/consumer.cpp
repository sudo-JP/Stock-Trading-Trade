#include "consumer.hpp"

bool connection = true; 

void consumer(int id, TCPClient client, TaskPool tp) {
    std::vector<std::function<void()>> works; 
    while (connect) {
        works = tp.getWork(); 
        for (auto work : works) {
            work();
        }
        BinaryMessage msg; 
        client.send_data(msg, (void *)true, 0);
    }
}
