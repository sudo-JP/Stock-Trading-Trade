FROM ubuntu:latest 

RUN apt-get update && apt-get install -y build-essential cmake ninja-build

WORKDIR /app

COPY ./CMakeLists.txt .

COPY ./src ./src

COPY . . 

RUN mkdir -p build 

WORKDIR /app/build

RUN cmake .. -G Ninja && ninja

WORKDIR /app

CMD [ "./build/main" ]
