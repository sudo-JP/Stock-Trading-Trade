FROM ubuntu:latest 

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    ninja-build \ 
    protobuf-compiler \ 
    libprotobuf-dev \ 
    git \
    wget \
    unzip \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . . 

RUN chmod +x setup_api.sh && ./setup_api.sh

RUN mkdir -p build 

WORKDIR /app/build

RUN cmake .. -G Ninja && ninja

WORKDIR /app

CMD [ "./build/src/trade" ]
