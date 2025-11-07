#include "engine.hpp"
#include <vector>


void Engine::start(size_t num_threads) {
    threads_prod.reserve(num_threads); 
    threads_cons.reserve(num_threads); 

    // Starting from 1 because each thread is listening
    // on its id + client/server.port. The client/server port 
    // are reserved for main to handle protocol and handshake
    for (size_t i = 1; i <= num_threads; i++) {
        // ref for threads see the object, not the copy
        threads_cons.emplace_back(consumer, i, std::ref(client), std::ref(tp), std::ref(connection));
        threads_prod.emplace_back(producer, i + num_threads, std::ref(server), std::ref(tp), std::ref(connection));
    }
} 

