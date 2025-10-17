# Stock Trading Trade

This project is connected to the other two repositories. Different repos for better encapsulation, since these projects will be run on separate Proxmox containers: 

[ML](https://github.com/sudo-JP/Stock-Trading-ML)

[Database](https://github.com/sudo-JP/Stock-Trading-DB)

Current architecure. Project is still in progress, so lots of empty files for now. 

```bash
.
├── build.sh
├── CMakeLists.txt
├── compose.yaml
├── Dockerfile
├── LICENSE
├── Makefile
├── README.md
└── src
    ├── CMakeLists.txt
    ├── core
    │   ├── config
    │   │   ├── config.cpp
    │   │   └── config.h
    │   ├── status.h
    │   └── utils
    │       ├── logger.h
    │       ├── threading
    │       └── time_utils.h
    ├── execution
    │   ├── order_manager.h
    │   └── risk
    │       ├── limits.h
    │       └── risk_engine.h
    ├── main.cpp
    ├── market_data
    │   ├── handlers
    │   ├── market_data_engine.h
    │   └── processors
    └── networking
        ├── alpaca
        │   ├── models
        │   │   ├── account_model.h
        │   │   ├── asset_model.h
        │   │   ├── order_model.h
        │   │   └── position_model.h
        │   └── services
        │       ├── account
        │       │   ├── account_service.cpp
        │       │   └── account_service.h
        │       ├── asset
        │       │   ├── asset_service.cpp
        │       │   └── asset_service.h
        │       ├── order
        │       │   ├── order_service.cpp
        │       │   └── order_service.h
        │       └── position
        │           ├── position_service.cpp
        │           └── position_service.h
        ├── internal
        │   └── api_server.h
        └── tcp
            ├── client
            │   ├── tcp_client.cpp
            │   └── tcp_client.h
            ├── common
            │   ├── message.h
            │   └── protocol.h
            └── server

```
