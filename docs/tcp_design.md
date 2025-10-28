# TCP System Design

## Overview
TCP Binary Protocol for extremely low-latency communication with the Rust backend, and a bit of Python ML for handshake/shutdown. Little-endian format is assumed. 

## Components

### 1. Handshake Protocol
- **Purpose**: synchronize threads/processes between C++ frontend and Rust backend/Python ML.
- **Flow**: initial connection → handshake exchange → confirmation.
- **Struct Layout**: The handshake struct is wrapped in `#pragma pack(1)` and `#pragma pack()` to prevent the compiler from adding padding bytes.

```cpp
struct Handshake {
    uint32_t thread_count;
    uint32_t port_range; 

};```


### 2. Graceful Shutdown Protocol
- **Purpose:** notify threads and backend/ML that the system is shutting down, allowing a clean exit.  
- **Flow**: backend or frontend sends shutdown signal → threads exit → connections close.
- **Struct Layout:** wrapped in `#pragma pack(push, 1)` / `#pragma pack(pop)` to prevent padding.
  ```cpp
  struct Shutdown {
      uint32_t shutdown_flag; // 0 = continue, 1 = shutdown
      uint32_t exit_code;     // optional code to indicate reason for shutdown
  };

### 3. Message / Payload Structures
All structs are wrapped in `#pragma pack(1)` and `#pragma pack()` to prevent the compiler from adding padding bytes.  
The expected byte order (endianness) is Little Endian, as produced by the Rust backend.  
All fixed-size arrays (e.g., `char account_id[64]`) are treated as raw bytes and may not be null-terminated.  
Double and integer fields are assumed to be standard IEEE-754 / two’s complement formats.
```cpp
struct AccountBinaryPayload { 
    char account_id[64];      
    char currency[4];         // Currency, default 'USD'
    
    double buying_power; 
    double cash;
    double portfolio_value; 
    double equity; 

    double unrealized_pl; 
    double realized_pl;

    uint32_t status;         
    int64_t last_update;      // This represents time in Nanosecond
};
```
```cpp
AssetBinaryPayload {
    char id[64];
    char asset_class[16];
    char exchange[16];
    char symbol[16];
    char name[32];
    uint32_t status;
    char tradeable;
    char marginable; 
    char shortable;
    char easy_to_borrow;
    char fractionable;
};
```
```cpp 
struct OrderBinaryPayload {
    char id[64];
    char client_order_id[64];

    int64_t created_at;       -> This represents time in Nanosecond
    int64_t updated_at;       -> This represents time in Nanosecond
    int64_t submitted_at;     -> This represents time in Nanosecond 
    int64_t filled_at;        -> This represents time in Nanosecond
    
    char symbol[16];
    char side[8];
    char type[16];

    uint32_t qty;
    uint32_t filled_qty;
    float filled_avg_price;

    char time_in_force[8];
};```
```cpp
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
};```


### 4. Connection Lifecycle
- **Server setup:** TCP server binds to the agreed port range and listens for incoming connections from Rust backend.  
- **Accepting connections:** Each accepted connection corresponds to a thread or logical channel for data transfer.  
- **Closing connections:** Cleanly close sockets on graceful shutdown or error conditions.  
- **Error handling:** handle reconnects, timeouts, and malformed packets without crashing threads.

### 5. Performance Considerations
- Use **fixed-size structs** (via `#pragma pack(1)`) for predictable, cache-friendly layout.  
- **Minimal dynamic allocations** in the TCP path; allocate buffers upfront when possible.  
- Support **buffering, batching, or pipelining** to maximize throughput for high-frequency message exchange.

### 6. Optional / Future-proofing
- **Protocol versioning:** allow backward-compatible changes in struct layout or handshake.  
- Maintain **logging or metrics hooks** for throughput, latency, and error rates.  
- Consider **extensible payloads** for future message types without breaking existing consumers.
