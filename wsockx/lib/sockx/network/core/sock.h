#pragma once

#include <netinet/in.h>
#include <sys/socket.h>

class Sock
{
protected:
    int fd;
    int conn;

    struct sockaddr_in addr;

public:
    Sock(u_short domain, int type, int proto, int port, u_long dev);

protected:
    virtual int attach(int sock, struct sockaddr_in addr) = 0;
};