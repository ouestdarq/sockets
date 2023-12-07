#pragma once

#include <stdlib.h>

#include <netinet/in.h>
#include <sys/socket.h>

namespace Proxymurder
{
    class Socket
    {
    protected:
        int sock;
        int connection;
        struct sockaddr_in address;

    public:
        Socket(u_short domain, int type, int proto, int port, u_long dev);

        virtual int attach(int sock, struct sockaddr_in address) = 0;
    };

    class Host : public Socket
    {
    public:
        Host(u_short domain, int type, int proto, int port, u_long dev)
            : Socket(domain, type, proto, port, dev){};
        int attach(int sock, struct sockaddr_in address);
    };

    class Client : public Socket
    {
    public:
        Client(u_short domain, int type, int proto, int port, u_long dev)
            : Socket(domain, type, proto, port, dev){};
        int attach(int sock, struct sockaddr_in address);
    };
}