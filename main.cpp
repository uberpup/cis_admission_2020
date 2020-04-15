#include <iostream>

#include "server.h"
#include "client.h"
#include "syscall_data.h"

int main() {
    Server server("127.0.0.1", 2222);
    // fork + server Operate
    pid_t server_pid = fork();
    if (server_pid == 0) {
        server.Operate();
    }


    Client client_first("127.0.0.1", 2221);
    Client client_second("127.0.0.1", 2220);
    // fork for each client
    pid_t client_first_pid = fork();
    if (client_first_pid == 0) {
        SyscallData data_first = {1};
        client_first.RemoteSyscall(&data_first);
    }
    pid_t client_second_pid = fork();
    if (client_second_pid == 0) {
        SyscallData data_second = {2};
        client_first.RemoteSyscall(&data_second);
    }

    /* std::cout << "Результат выполнения: " << client_first.HasSucceed() << " "
            << client_second.HasSucceed() << std::endl; */

    return 0;
}
