#pragma once

#include <network/sockets/sock.h>

#define BACKLOG 10

class Host : public Sock
{
public:
    Host(u_short domain, int type, int proto, int port, u_long dev);

protected:
    int attach(int fd, struct sockaddr_in addr);
    void run();
};
