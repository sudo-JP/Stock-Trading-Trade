#include "networking/tcp/client/tcp_client.hpp"
#include "core/utils/threading/task_pool.hpp"

#ifndef _CONSUMER_H_
#define _CONSUMER_H_
void consumer(int id, TCPClient client, TaskPool tp); 

#endif 
