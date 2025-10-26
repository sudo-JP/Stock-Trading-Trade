#include <vector>
#include <cstdint>
#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_


// Binary Protocol 

#pragma pack(1)
struct BinaryMessage {
    uint32_t sql_command; 
    uint32_t table; 
    uint64_t timestamp; 
    uint32_t data_size; 
    //char payload[];
};

// Explicit definition of enum so that it doesn't change the size
// for bytes 

enum class SQLCommand : uint32_t {
    INSERT = 1, 
    SELECT = 2, 
    UPDATE = 3,
    DELETE = 4 
}; 

enum class SQLTable : uint32_t {
    ACCOUNT = 1,
    ORDER = 2, 
    POSITION = 3, 
    INSTRUMENT = 4, 
}; 

#pragma pack()

std::vector<uint8_t> serialize(const BinaryMessage &msg, const void *payload, size_t payload_size);
//deserialize(const std::string &data);
#endif 
