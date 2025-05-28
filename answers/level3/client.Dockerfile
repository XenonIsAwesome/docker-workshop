FROM ubuntu:latest

RUN apt update && apt install -y gcc g++ cmake

WORKDIR /build
COPY src src
COPY CMakeLists.txt CMakeLists.txt

RUN mkdir -p /build/build/ && \
    cd /build/build/ && \
    cmake .. && make -j$(nproc)

ENTRYPOINT [ "/build/build/client" ]