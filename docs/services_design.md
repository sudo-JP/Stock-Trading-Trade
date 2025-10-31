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

### Position 
```javascript
[
  {
    'asset_id': '4ce9353c-66d1-46c2-898f-fce867ab0247',
    'symbol': 'NVDA',
    'exchange': 'NASDAQ',
    'asset_class': 'us_equity',
    'asset_marginable': True,
    'qty': '1',
    'avg_entry_price': '206.07',
    'side': 'long',
    'market_value': '202.5',
    'cost_basis': '206.07',
    'unrealized_pl': '-3.57',
    'unrealized_plpc': '-0.0173242102198282',
    'unrealized_intraday_pl': '-3.57',
    'unrealized_intraday_plpc': '-0.0173242102198282',
    'current_price': '202.5',
    'lastday_price': '202.89',
    'change_today': '-0.0019222238651486',
    'qty_available': '1'
  }
]
```
