#include <sys/socket.h>
#include <stdexcept>
#include <cstdint>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "general_utils.h"

namespace utils::net {
    enum AddrFamily {
        IPV4 = AF_INET,
        IPV6 = AF_INET6, // Not supported
        UDS = AF_UNIX, // Not supported
    };

    enum SocketProtocol {
        TCP = SOCK_STREAM,
        UDP = SOCK_DGRAM,
    };

    // server
    void bind_and_listen(FD socket_fd, const std::string& host, uint16_t port, AddrFamily family);
    FD accept_connection(FD socket_fd);

    // client
    void connect(FD socket_fd, const std::string& host, uint16_t port, AddrFamily family);

    FD create_socket(AddrFamily addr_family, SocketProtocol proto);
    sockaddr_in *make_sockaddr(const std::string& host, uint16_t port, AddrFamily family);

    template <typename T>
    void send(FD socket_fd, const T* buf, size_t num_of_elements) {
        ::send(socket_fd, reinterpret_cast<const void *>(buf), sizeof(T) * num_of_elements, 0);
    }

    template <typename T>
    void recv(FD socket_fd, T* buf, size_t num_of_elements) {
        ::recv(socket_fd, reinterpret_cast<void *>(buf), sizeof(T) * num_of_elements, 0);
    }

}