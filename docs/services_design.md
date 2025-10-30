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
    "asset_id": "b0b6dd9d-8b9b-48a9-ba46-b9d54906e415",
    "symbol": "AAPL",
    "exchange": "NASDAQ",
    "asset_class": "us_equity",
    "avg_entry_price": "175.25",
    "qty": "10",
    "side": "long",
    "market_value": "1782.50",
    "cost_basis": "1752.50",
    "unrealized_pl": "30.00",
    "unrealized_plpc": "0.0171184022824536",
    "unrealized_intraday_pl": "15.00",
    "unrealized_intraday_plpc": "0.00849999999999999",
    "current_price": "178.25",
    "lastday_price": "176.75",
    "change_today": "0.00849999999999999",
    "asset_marginable": true
  },
  {
    "asset_id": "b535316e-826a-4934-9214-e275f7e7f6e2",
    "symbol": "TSLA",
    "exchange": "NASDAQ",
    "asset_class": "us_equity",
    "avg_entry_price": "301.10",
    "qty": "-5",
    "side": "short",
    "market_value": "-1497.50",
    "cost_basis": "-1505.50",
    "unrealized_pl": "8.00",
    "unrealized_plpc": "0.00531393666993512",
    "unrealized_intraday_pl": "10.00",
    "unrealized_intraday_plpc": "0.00667954848972173",
    "current_price": "299.50",
    "lastday_price": "301.50",
    "change_today": "-0.0066334991708819",
    "asset_marginable": true
  }
]
```
