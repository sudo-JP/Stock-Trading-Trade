#include "networking/tcp/client/tcp_client.hpp"
#include "core/utils/threading/task_pool.hpp"
#include "execution/engine.hpp"

#ifndef _CONSUMER_H_
#define _CONSUMER_H_
void consumer(int id, TCPClient &client, TaskPool &tp, std::atomic<bool> &connection);

#endif 
