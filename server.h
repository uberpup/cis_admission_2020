#ifndef CIS_ADMISSION_SERVER_H
#define CIS_ADMISSION_SERVER_H

#include <arpa/inet.h>
#include <csignal>
#include <cstdlib>
#include <netinet/in.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/syscall.h>
#include <unistd.h>

#include "syscall_data.h"

class Server {
public:
    Server() = default;
    Server(const char* ip_string, short port_num);
    void Operate();

private:
    static void* ClientHandler(void* arg);    // void* is required return value type for pthreads

    void SignalHandler(int sig_id) {
        if (sig_id == SIGTERM) {
            signal_caught = 1;
        } else if (sig_id == SIGINT) {
            signal_caught = 2;
        }
    }

    int sock_fd_;
    sig_atomic_t signal_caught = 0;
};

#endif //CIS_ADMISSION_SERVER_H
