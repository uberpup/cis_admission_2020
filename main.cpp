#include <iostream>

#include "server.h"
#include "client.h"
#include "syscall_data.h"

int main() {
    Server server("127.0.0.1", 2222);
    // fork + server Operate

    Client client_first("127.0.0.1", 2221);
    Client client_second("127.0.0.1", 2220);
    // fork for each client

    SyscallData data_first = {};
    SyscallData data_second = {};

    // Внимательно сделать пример корректным

    client_first.RemoteSyscall(&data_first);
    client_second.RemoteSyscall(&data_second);

    std::cout << "Результат выполнения: " << client_first.HasSucceed() << " "
            << client_second.HasSucceed() << std::endl;

    return 0;
}
