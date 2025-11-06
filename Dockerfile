FROM gcc:latest

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    ninja-build \
    libssl-dev  

WORKDIR /app

COPY . .

RUN make 

CMD ["make run"]
