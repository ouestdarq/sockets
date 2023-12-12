#pragma once

#include "sock.h"

class Host : public Sock
{
public:
    Host(u_short domain, int type, int proto, int port, u_long dev);

protected:
    int attach(int sock, struct sockaddr_in addr);
};
