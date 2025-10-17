#include <string>
#include <chrono>
#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

struct TCPMessage {
    std::string command;  
    std::string data; 
    std::chrono::system_clock::time_point time; 
}; 

std::string serialize(const TCPMessage &msg);
TCPMessage deserialize(const std::string &data);

#endif 
