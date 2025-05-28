FROM ubuntu:latest

RUN apt update && apt install -y gcc g++ cmake

WORKDIR /build
COPY src src
COPY CMakeLists.txt CMakeLists.txt

RUN mkdir -p /build/build/ && \
    cd /build/build/ && \
    cmake .. && make -j$(nproc)

FROM ubuntu:latest AS server
COPY --from=0 /build/build/server /app/docker-workshop

ENTRYPOINT [ "/app/docker-workshop" ]

FROM ubuntu:latest AS client
COPY --from=0 /build/build/client /app/docker-workshop

ENTRYPOINT [ "/app/docker-workshop" ]