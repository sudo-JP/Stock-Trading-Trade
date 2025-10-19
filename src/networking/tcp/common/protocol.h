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

// Binary Protocol 

#pragma pack(push, 1)

struct BinaryMessage {
    uint32_t sql_command; 
    uint32_t table; 
    uint64_t timestamp; 
    uint32_t data_size; 
    //char payload[];
};

enum SQLCommand {
    INSERT, 
    SELECT, 
    UPDATE,
    DELETE 
}; 

enum SQLTable {
    ACCOUNT,
    ORDER, 
    POSITION, 
    INSTRUMENT, 
}; 

// Times are represented in nanoseconds 

struct OrderBinaryPayload {
    char id[64];
    char client_order_id[64];
    uint64_t created_at;
    uint64_t updated_at;
    uint64_t submitted_at;
    uint64_t filled_at;
    
    char symbol[8];
    char side[4];
    char type[16];
    uint64_t time_in_force;

    uint32_t filled_qty;
    float filled_avg_price;
};

#pragma pack(pop)

#endif 
