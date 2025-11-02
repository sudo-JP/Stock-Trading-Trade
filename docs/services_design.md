# Service System Design

## Overview

The service layer handles all HTTP interactions with external APIs (e.g., Alpaca).  
It translates high-level operations (GET/POST requests with arguments) into low-level binary payloads suitable for transmission over the TCP network to other system components.

Key points:  
- Acts as the bridge between network protocols and internal execution logic.  
- Each module is responsible for a specific domain: orders, assets, positions, or account data.  
- Modules can generate closures that are enqueued in the `TaskPool` for threaded execution.  
- Services are mostly stateless for concurrency simplicity, except for read-only caches where necessary (e.g., account/position snapshots).

## Components

### Caching
- Applied in `AccountService` and `PositionService` to prevent blocking I/O.  
- Maintains a local snapshot of data for efficient access and concurrent reads.

### Lifecycle
- Each service class is instantiated once (singleton).  
- Threads only invoke methods; they do not create their own instances.  
- Simplifies thread safety, since state is minimal and mostly read-only.

### Error Handling
- Faulty or incomplete HTTP data is replaced with default values in the binary payload struct.  
- If all data is invalid, a try-catch block logs the error to `stderr`.  
- Ensures that one failed request does not crash the system or block worker threads.
