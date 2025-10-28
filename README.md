# Stock Trading Trade

This project is connected to the other two repositories. Different repos for better encapsulation, since these projects will be run on separate Proxmox containers: 

[ML](https://github.com/sudo-JP/Stock-Trading-ML)

[Database](https://github.com/sudo-JP/Stock-Trading-DB)

Current architecure. Project is still in progress, so lots of empty files for now. 

All detailed architecture and system design documentation is available in the `/docs` folder.  
You can find:

- Threading system design (`threading.md`)  
- Service layer design (`services.md`)  
- TCP protocol and payloads (`tcp.md`)  

For implementation details and usage, please refer to the respective files in `/docs`.

```bash
.
├── docs
└── src
    ├── core
    │   ├── config
    │   └── utils
    │       └── threading
    └── networking
        ├── alpaca
        │   ├── models
        │   └── services
        │       ├── account
        │       ├── asset
        │       ├── order
        │       └── position
        └── tcp
            ├── client
            ├── common
            └── server
```
