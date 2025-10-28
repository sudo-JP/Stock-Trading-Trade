# Developer Checklist 

## Services
- [x] Account models 
- [x] Position models 
- [x] Order models 
- [x] Asset models 
- [x] Account Service class with GET 
- [x] Position Service class with GET 
- [x] Asset Service class with GET 
- [x] Order Service class with POST 
- [x] Testing if HTTP Request work 
- [x] Error checking 
- [ ] Make AccountService methods async 
- [ ] Make OrderService methods async 
- [ ] Make PositionService methods async 
- [ ] Make AssetService methods async 
- [ ] Documentation 

## Threading 
- [x] TaskPool class 
- [x] Producer method for pushing work to TaskPool
- [x] CHUNK-based consumer method for getting tasks from TaskPool
- [ ] Producer thread lifecycle: receive TCP data → create closures → push to TaskPool
- [ ] Consumer thread lifecycle: pop closures → execute → handle errors → repeat until system_down
- [ ] Set system_down flag → wake all threads → join threads → close connections

## TCP/Networking
- [x] BinaryMessage struct 
- [x] Define low-level binary structs for account/position/order/asset
- [x] Serialize data to be sent to backend 
- [x] TCP Client class to establish connection 
- [x] Test for sending message 
- [x] Handshake protocol
- [x] Shutdown protocol 
- [ ] Deserialize data to receive ML's signal 
- [ ] Convert to closures / TaskPool work items
- [ ] Handle malformed or incomplete packets

## Main 
- [x] Initial handshake protocol 
- [x] Graceful shutdown protocol 
- [ ] Spawn producer threads
- [ ] Spawn consumer threads
- [ ] Worker life cycle 
- [ ] Close TCP connections after all threads finish
