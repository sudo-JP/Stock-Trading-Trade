# C++ Frontend Architecture

## Overview

The C++ frontend acts as the high-performance execution layer, receiving signals from the ML backend (Rust + Python), translating them into concrete trading operations, and communicating with the Rust backend for persistent state updates. It leverages **threaded execution**, **TaskPool queues**, and **service modules** to maximize concurrency while maintaining low latency.

Key goals:

- Low-latency binary TCP communication.
- Thread-safe, high-throughput task execution.
- Clear separation of service logic, network handling, and task execution.
- Graceful shutdown and system lifecycle management.

---

## Components

### 1. TaskPool

- **Purpose:** Dynamic work queue for producers (receiving ML signals) and consumers (executing operations).  
- **Structure:**  
  - `std::deque<std::function<void()>> works` – closures encapsulating tasks.  
  - `std::mutex mtx` + `std::condition_variable cv` – synchronizes producers and consumers.  
- **Key points:**  
  - Supports bulk pop (`CHUNK`) to reduce lock contention.  
  - Producers push closures; consumers pop and execute.  
  - Dynamically grows as tasks are inserted.  
- **Methods:**  
  - `add_work()` – push one or more closures to the queue.  
  - `get_work()` – pop up to `CHUNK` closures.

---

### 2. Thread Lifecycle

All threads follow a structured lifecycle to maintain synchronization and enable graceful shutdown:

1. **Thread Initialization**
   - Establish handshake protocol with Rust backend and Python ML to negotiate thread count and ports.
   - Thread registers itself as producer or consumer.
   - Associate with `system_down` flag for graceful exit.

2. **Wait for System Ready**
   - Consumer blocks on CV if the task queue is empty.  
   - Producer waits for handshake completion before producing tasks.

3. **Main Execution Loop**
   - **Consumer threads:**  
     1. Pop closures from TaskPool (up to `CHUNK`).  
     2. Execute each closure with full context (service instances, parameters).  
     3. Catch and handle errors locally to prevent thread crashes.  
     4. Repeat until `system_down` is set.
   - **Producer threads:**  
     1. Receive TCP signals from Rust backend.  
     2. Convert signals into closures referencing service methods.  
     3. Push closures to TaskPool.  
     4. Repeat until `system_down` is set.

4. **Graceful Shutdown**
   - `system_down` flag set → CV notifies all threads → threads exit loops → join threads → close connections.

---

### 3. Service Layer

- **Purpose:** Handles HTTP requests to external APIs (e.g., Alpaca) and translates results into binary payloads.  
- **Design:** Mostly stateless to simplify thread safety, except for read-only caching in `AccountService` and `PositionService`.  
- **Components:**  
  - **Caching:** Local snapshots to prevent blocking I/O.  
  - **Singleton Lifecycle:** Each service is initialized once; threads share the same instance.  
  - **Error Handling:** Defaults for incomplete data, exceptions logged to `stderr`.  
- **Async Wrapper:**  
  - Private synchronous method: `getAccountSync()`.  
  - Public async method: `getAccount()` returning `std::future<AccountBinaryPayload>`.  
  - Pattern repeated across all service modules (Position, Order, Asset).

---

### 4. TCP / Networking

- **Purpose:** Low-latency binary communication with Rust backend.  
- **BinaryMessage Protocol:**  
  - `sql_command` → INSERT, SELECT, UPDATE, DELETE  
  - `table` → ACCOUNT, ORDER, POSITION, INSTRUMENT  
  - `type` → MessageType (HANDSHAKE, SHUTDOWN, SIGNAL, etc.)  
- **Payload Structures:** All structs wrapped in `#pragma pack(1)` to prevent padding; Little Endian expected.  
- **Handshake Protocol:** Synchronize threads with Rust backend (thread count, port range).  
- **Graceful Shutdown:** Notify all threads and backend that system is exiting.  
- **Client Implementation:**  
  - `TCPClient::send_data(BinaryMessage, void* payload, size_t payload_size)`  
  - `serialize()` converts struct + payload into raw bytes.  

---

### 5. Main Flow

1. Establish environment variables and configuration.
2. Initialize TCP client and perform handshake.
3. Spawn producer and consumer threads according to negotiated count.  
4. Producers push closures to TaskPool as TCP messages arrive.  
5. Consumers execute closures, potentially invoking async service methods.  
6. On shutdown signal: set `system_down`, notify threads, join threads, close TCP connections.

---

### 6. Key Design Principles

- **Separation of Concerns:** Networking, services, threading, and execution logic are distinct modules.  
- **Low-latency:** Fixed-size binary structs, minimal allocations, bulk queue operations.  
- **Thread Safety:** TaskPool synchronized with mutex + CV; services mostly stateless.  
- **Extensibility:** Support for new message types, future ML integrations, and protocol versioning.  
