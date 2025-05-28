#include "net_utils.h"
#include <errno.h>
#include <string.h>
#include <iostream>

namespace utils::net {
    sockaddr_in *make_sockaddr(const std::string& host, uint16_t port, AddrFamily family) {
        sockaddr_in *socket_addr = new (std::nothrow) sockaddr_in();

        memset(socket_addr, 0, sizeof(sockaddr_in));

        socket_addr->sin_family = family;
        socket_addr->sin_addr.s_addr = inet_addr(host.c_str());
        socket_addr->sin_port = htons(port);

        return socket_addr;
    }

    FD create_socket(AddrFamily addr_family, SocketProtocol proto) {
        FD socket_fd = ::socket(addr_family, proto, 0);
        if (!is_valid_fd(socket_fd)) {
            std::cerr << strerror(errno) << std::endl;
            throw std::runtime_error("Could not create socket.");
        }
        return socket_fd;
    };

    void bind_and_listen(FD socket_fd, const std::string& host, uint16_t port, AddrFamily family) {
        auto *socket_addr = make_sockaddr(host, port, family);
        auto result = ::bind(socket_fd, reinterpret_cast<sockaddr*>(socket_addr), sizeof(sockaddr_in));
        
        if (result < 0) {
            std::cerr << strerror(errno) << std::endl;
            throw std::runtime_error("Could not bind to address");
        }

        static constexpr int MAX_CONNECTIONS = 1;
        result = ::listen(socket_fd, MAX_CONNECTIONS);

        if (result < 0) {
            std::cerr << strerror(errno) << std::endl;
            throw std::runtime_error("Could not listen to connections");
        }
    }

    FD accept_connection(FD socket_fd) {
        FD connection_fd = ::accept(socket_fd, nullptr, nullptr);
        if (!is_valid_fd(connection_fd)) {
            std::cerr << strerror(errno) << std::endl;
            throw std::runtime_error("Could not accept connection.");
        }

        return connection_fd;
    }


    void connect(FD socket_fd, const std::string &host, uint16_t port, AddrFamily family) {
        auto *socket_addr = make_sockaddr(host, port, family);

        auto result = ::connect(socket_fd, reinterpret_cast<sockaddr*>(socket_addr), sizeof(sockaddr_in));
        if (result < 0) {
            std::cerr << strerror(errno) << std::endl;
            throw std::runtime_error("Could not connect to host");
        }
    }
}