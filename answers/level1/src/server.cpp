#include <iostream>
#include <utils/net_utils.h>

int main(int argc, char** argv) {
    auto family = utils::net::AddrFamily::IPV4;
    auto proto = utils::net::SocketProtocol::TCP;
    const std::string host = utils::get_env_or_default("BIND_ADDRESS", "0.0.0.0");
    uint16_t port = std::stoi(utils::get_env_or_default("PORT", "9999"));

    utils::FD socket_fd = utils::net::create_socket(family, proto);
    utils::net::bind_and_listen(socket_fd, host, port, family);
    std::cout << "Server listening on " << host << ":" << std::to_string(port) << std::endl;

    utils::FD connection_fd = utils::net::accept_connection(socket_fd);

    char *data = new char[10000];
    while (true) {
        utils::net::recv(connection_fd, data, 10000);
        std::cout << data << std::endl;
    }
}