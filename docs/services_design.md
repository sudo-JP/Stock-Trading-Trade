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



## Order 
```javascript
{
  'id': '7817ed16-04f0-44b6-b03c-67a5a70d3e23',
  'client_order_id': 'a2caff27-178d-4004-852e-4cbcfa5ac56c',
  'created_at': '2025-10-30T21:43:02.040468067Z',
  'updated_at': '2025-10-30T21:43:02.042088036Z',
  'submitted_at': '2025-10-30T21:43:02.040468067Z',
  'filled_at': None,
  'expired_at': None,
  'canceled_at': None,
  'failed_at': None,
  'replaced_at': None,
  'replaced_by': None,
  'replaces': None,
  'asset_id': '4ce9353c-66d1-46c2-898f-fce867ab0247',
  'symbol': 'NVDA',
  'asset_class': 'us_equity',
  'notional': None,
  'qty': '1',
  'filled_qty': '0',
  'filled_avg_price': None,
  'order_class': '',
  'order_type': 'market',
  'type': 'market',
  'side': 'buy',
  'position_intent': 'buy_to_open',
  'time_in_force': 'gtc',
  'limit_price': None,
  'stop_price': None,
  'status': 'accepted',
  'extended_hours': False,
  'legs': None,
  'trail_percent': None,
  'trail_price': None,
  'hwm': None,
  'subtag': None,
  'source': None,
  'expires_at': '2026-01-29T21:00:00Z'
}
```
