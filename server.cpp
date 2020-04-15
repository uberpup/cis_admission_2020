#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>

#include "server.h"

Server::Server(const char* ip_string, short port_num) {
    sock_fd_ = socket(AF_INET, SOCK_STREAM, 0);

    if (ip_string == nullptr) {
        ip_string = "127.0.0.1";  // localhost
    }

    struct sockaddr_in scaddr = {.sin_family = AF_INET,
                                 .sin_addr = inet_addr(ip_string),
                                 .sin_port = htons(port_num)};

    bind(sock_fd_, (struct sockaddr*)&scaddr, sizeof(scaddr));

    listen(sock_fd_, SOMAXCONN);
}


void Server::Accept() {
}