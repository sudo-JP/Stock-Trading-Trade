#include <vector>
#include <cstdint>
#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_


// Binary Protocol 

#pragma pack(1)

// Explicit definition of enum so that it doesn't change the size
// for bytes 
enum class MessageType : uint32_t {
    HANDSHAKE = 1,
    SHUTDOWN = 2,
    DB_OP = 3
};

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

struct BinaryMessage {
    MessageType type; 
    SQLTable table; 
    SQLCommand sql_command; 
    uint32_t data_size; 
};

struct Handshake {
    uint32_t thread_count;  
    uint32_t port_range; 
};

struct Shutdown {
    uint32_t shutdown_flag; 
    uint32_t exit_code; 
}; 
#pragma pack()

std::vector<uint8_t> serialize(const BinaryMessage &msg, const void *payload, size_t payload_size);
//deserialize(const std::string &data);
#endif 
