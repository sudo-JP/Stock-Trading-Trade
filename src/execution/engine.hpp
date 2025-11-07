#include <atomic>
#include <thread>
#include "core/config/config.hpp"
#include "execution/producer/producer.hpp"
#include "execution/consumer/consumer.hpp"

class Engine {
    public: 
        Engine(TaskPool &tp_t, TCPServer &serv, TCPClient &cli) 
        : tp(tp_t),
        server(serv),
        client(cli)
        {}; 
        void start(size_t num_threads); 
        void stop();
        bool connected();
    private: 
        std::atomic<bool> connection{true};
        TaskPool &tp; 
        TCPServer &server; 
        TCPClient &client;
        std::vector<std::thread> threads_prod;     
        std::vector<std::thread> threads_cons;     

}; 
