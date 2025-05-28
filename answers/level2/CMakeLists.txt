cmake_minimum_required(VERSION 3.10)
project(docker-workshop)

set(CMAKE_CXX_STANDARD 20)

# Glob all utility source and header files
file(GLOB UTILS_SRC
    "src/utils/*.cpp"
    "src/utils/*.h"
)

include_directories(src)

# Server target
add_executable(server
    src/server.cpp
    ${UTILS_SRC}
)

# Client target
add_executable(client
    src/client.cpp
    ${UTILS_SRC}
)