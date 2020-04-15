#ifndef CIS_ADMISSION_CLIENT_H
#define CIS_ADMISSION_CLIENT_H

#include "syscall_data.h"

//TODO mmap for pointers - ?

class Client {
public:
    Client() = default;
    Client(const char* ip_string, short port_num);

    void RemoteSyscall(SyscallData* syscall_data);

    bool HasSucceed() {
        return responded;
    }
private:
    void SendRequest(int sock, SyscallData* syscall_data);
    int64_t RecvResponse(int sock);

    int sock_fd_;
    bool responded = false;
};

#endif //CIS_ADMISSION_CLIENT_H
