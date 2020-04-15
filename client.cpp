#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/syscall.h>
#include <thread>
#include <unistd.h>

#include "client.h"

Client::Client(const char* ip_string, short port_num) {
    sock_fd_ = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in scaddr = {.sin_family = AF_INET,
            .sin_addr = inet_addr(ip_string),
            .sin_port = htons(port_num)};

    connect(sock_fd_, (sockaddr*)&scaddr, sizeof(scaddr));
}

void Client::RemoteSyscall(SyscallData* syscall_data) {
    if (sock_fd_ != -1) {
        SendRequest(sock_fd_, syscall_data);
        std::cout << "Syscall execution result: " << RecvResponse(sock_fd_) << std::endl;
        responded = true;
    } else {
        std::cout << "Socked is invalid" << std::endl;
    }
}

void Client::SendRequest(int sock, SyscallData* syscall_data) {
    write(sock, (char*)syscall_data, sizeof((char*)syscall_data));
}

int64_t Client::RecvResponse(int sock) {
    int64_t response = 0;
    read(sock, (char*)&response, sizeof(&response));
    return response;
}