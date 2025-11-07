#include "networking/tcp/server/tcp_server.hpp"
#include "core/utils/threading/task_pool.hpp"

#ifndef _PRODUCER_H_
#define _PRODUCER_H_
void producer(int id, TCPServer &server, TaskPool &tp, std::atomic<bool> &connection); 

#endif 
