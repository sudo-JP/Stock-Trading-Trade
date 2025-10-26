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

// Times are represented in nanoseconds 

struct OrderBinaryPayload {
    char id[64];
    char client_order_id[64];
    int64_t created_at;
    int64_t updated_at;
    int64_t submitted_at;
    int64_t filled_at;
    
    char symbol[16];
    char side[8];
    char type[16];
    int64_t time_in_force;

    uint32_t filled_qty;
    float filled_avg_price;
};


struct PositionBinaryPayload {
    char asset_id[64];
    char symbol[16];
    char exchange[16];
    char asset_class[16];

    uint32_t qty; 
    double avg_entry_price;
    
    char side[8];
    double market_value; 
    double cost_basis; 

    
    double unrealized_pl;
    double unrealized_plpc;
    double unrealized_intraday_pl;
    double unrealized_intraday_plpc;

    double current_price;
    double lastday_price;
    double change_today;
};


#pragma pack()

std::vector<uint8_t> serialize(const BinaryMessage &msg, const void *payload, size_t payload_size);
//deserialize(const std::string &data);
#endif 
