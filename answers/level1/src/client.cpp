#include <iostream>
#include <utils/net_utils.h>

int main(int argc, char** argv) {
    auto family = utils::net::AddrFamily::IPV4;
    auto proto = utils::net::SocketProtocol::TCP;
    const std::string host = utils::get_env_or_default("SERVER_HOST", "127.0.0.1");
    uint16_t port = std::stoi(utils::get_env_or_default("PORT", "9999"));

    utils::FD socket_fd = utils::net::create_socket(utils::net::AddrFamily::IPV4, proto);
    bool connected = false;

    while(!connected) {
        try {
            utils::net::connect(socket_fd, host, port, family);
            connected = true;
        } catch (std::runtime_error &e) {
            std::cerr << e.what() << std::endl;
        }
    }
    std::cout << "Connected to " << host << ":" << std::to_string(port) << std::endl;

    const std::string data = "Hello world!";
    
    while (true) {
        utils::net::send(socket_fd, data.data(), data.size());
    }
}