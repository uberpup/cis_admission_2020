#ifndef CIS_ADMISSION_SERVER_H
#define CIS_ADMISSION_SERVER_H

class Server {
public:
    Server() = default;
    Server(const char* ip_string, short port_num);
    void Accept();
private:
    int sock_fd_;
};

#endif //CIS_ADMISSION_SERVER_H
