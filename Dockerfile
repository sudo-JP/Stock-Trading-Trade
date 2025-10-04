FROM ubuntu:latest 

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    ninja-build \ 
    protobuf-compiler \ 
    libprotobuf-dev \ 
    git \
    wget 

WORKDIR /app

COPY . . 

RUN cd api/IBJts/source/IntelTBB/LIBRARY && \
    make CC=gcc CALL_BY_REF=0 GLOBAL_RND=0 GLOBAL_FLAGS=0 UNCHANGED_BINARY_FLAGS=0 && \
    cp libbid.a ../cppclient/


RUN mkdir -p build 

WORKDIR /app/build

RUN cmake .. -G Ninja && ninja

WORKDIR /app

CMD [ "./build/main" ]
