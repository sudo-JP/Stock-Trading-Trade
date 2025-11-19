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
    char is_arr; 
    uint32_t arr_len; 
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

struct TCPData {
    BinaryMessage bn; 
    void *payload; 
    size_t payload_size;
}; 

/*
 * caller of these functions must initialize their own BinaryMessage heaer 
 * that means the caller must be aware if the value put in is a struct or 
 * an array of struct 
 * */
std::vector<uint8_t> serialize(const BinaryMessage &msg, const void *payload, size_t payload_size);
std::vector<uint8_t> serialize(const BinaryMessage &msg, const std::vector<void *> &payload, size_t payload_size);

void *deserialize(std::vector<uint8_t> stream);
#endif 
