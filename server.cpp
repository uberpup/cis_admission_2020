#include "server.h"

Server::Server(const char* ip_string, short port_num) {
    sock_fd_ = socket(AF_INET, SOCK_STREAM, 0);

    if (sock_fd_ == -1) {
        exit(1);
    }

    if (ip_string == nullptr) {
        ip_string = "127.0.0.1";  // localhost
    }

    struct sockaddr_in scaddr = {.sin_family = AF_INET,
                                 .sin_addr = inet_addr(ip_string),
                                 .sin_port = htons(port_num)};

    if (bind(sock_fd_, (struct sockaddr*)&scaddr, sizeof(scaddr)) == -1) {
        exit(2);
    }

    if (listen(sock_fd_, 128) == -1) {  // 128 = SOMAXCONN on Linux
        exit(3);
    }
}

void Server::Operate() {
    while (signal_caught == 0) {
        int new_sock_fd = accept(sock_fd_, nullptr, nullptr);

        char* syscall_data[sizeof(SyscallData)];
        read(sock_fd_, syscall_data, sizeof(syscall_data));

        pthread_t client_thread;
        pthread_create(&client_thread, NULL, ClientHandler, (void*)syscall_data);

        int64_t syscall_rv = -1;
        pthread_join(client_thread, (void**)&syscall_rv);

        write(sock_fd_, (char*)&syscall_rv, sizeof((char*)&syscall_rv));    // Returning syscall rv to client

    }
    exit(0);
}

void* Server::ClientHandler(void* arg) {
    auto* s_data = static_cast<SyscallData*>(arg);
    std::ptrdiff_t syscall_rv = -1;

    switch (s_data->arg_num) {
        case 0:
            syscall_rv = syscall(s_data->syscall_number);
            break;
        case 1:
            syscall_rv = syscall(s_data->syscall_number, s_data->arg1);
            break;
        case 2:
            syscall_rv = syscall(s_data->syscall_number, s_data->arg1,
                    s_data->arg2);
            break;
        case 3:
            syscall_rv = syscall(s_data->syscall_number, s_data->arg1,
                    s_data->arg2, s_data->arg3);
            break;
        case 4:
            syscall_rv = syscall(s_data->syscall_number, s_data->arg1,
                    s_data->arg2, s_data->arg3, s_data->arg4);
            break;
        case 5:
            syscall_rv = syscall(s_data->syscall_number, s_data->arg1,
                    s_data->arg2, s_data->arg3, s_data->arg4, s_data->arg5);
            break;
        case 6:
            syscall_rv = syscall(s_data->syscall_number, s_data->arg1,
                    s_data->arg2, s_data->arg3, s_data->arg4, s_data->arg5,
                    s_data->arg6);
            break;
    }
    return (void*)syscall_rv;
}
