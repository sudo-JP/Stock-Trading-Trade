FROM gcc:latest

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    ninja-build \
    libssl-dev  

WORKDIR /app
COPY . .


ENTRYPOINT ["/bin/bash", "-c", "source /app/.env && mkdir -p build && cd build && rm -rf CMakeCache.txt CMakeFiles && cmake .. -G Ninja && ninja && cd .. && exec ./build/src/trade"]
