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

## API Calls 

### Account 
```javascript
Accountinfo: {
  'id': 'e178593c-3701-4dcc-9b6e-345be925368d',
  'admin_configurations': {
    
  },
  'user_configurations': None,
  'account_number': '',
  'status': 'ACTIVE',
  'crypto_status': 'ACTIVE',
  'options_approved_level': 3,
  'options_trading_level': 3,
  'currency': 'USD',
  'buying_power': '200000',
  'regt_buying_power': '200000',
  'daytrading_buying_power': '0',
  'effective_buying_power': '200000',
  'non_marginable_buying_power': '100000',
  'options_buying_power': '100000',
  'bod_dtbp': '0',
  'cash': '100000',
  'accrued_fees': '0',
  'portfolio_value': '100000',
  'pattern_day_trader': False,
  'trading_blocked': False,
  'transfers_blocked': False,
  'account_blocked': False,
  'created_at': '2025-10-13T05:54:33.35762Z',
  'trade_suspended_by_user': False,
  'multiplier': '2',
  'shorting_enabled': True,
  'equity': '100000',
  'last_equity': '100000',
  'long_market_value': '0',
  'short_market_value': '0',
  'position_market_value': '0',
  'initial_margin': '0',
  'maintenance_margin': '0',
  'last_maintenance_margin': '0',
  'sma': '100000',
  'daytrade_count': 0,
  'balance_asof': '2025-10-29',
  'crypto_tier': 1,
  'intraday_adjustments': '0',
  'pending_reg_taf_fees': '0'
}
```
