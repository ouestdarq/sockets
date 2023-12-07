#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "socket.h"

Socket::Socket(int domain, int type, int proto, int port, u_long dev)
{
    // this->addr = {
    //     sin_family : domain,
    //     sin_port : htons(port),
    //     sin_addr : {
    //         s_addr : htonl(dev),
    //     },
    // };
    this->addr.sin_family = domain;
    this->addr.sin_port = htons(port);
    this->addr.sin_addr.s_addr = htonl(dev);

    if ((this->sock = socket(domain, type, proto)) < 0)
        exit(1);
}

Host::Host(int domain, int type, int proto, int port, u_long dev)
    : Socket(domain, type, proto, port, dev)
{
    const char *hello = "HTTP/1.1 200 OK\
    Date: Fri, 06 Nov 2009 00:35:42 GMT\
    Server: Apache\
    Keep-Alive: timeout=15, max=100\
    Connection: Keep-Alive\
    Content-Type: text/plain\
    \
    fucking hell";

    int addrlen = sizeof(this->addr);
    int n;
    int r;
    if ((this->connection = this->attach(this->sock, this->addr)) < 0)
        exit(1);

    if (listen(this->sock, SIZESOC) < 0)
        exit(1);

    while (true)
    {
        if ((n = accept(this->sock, (struct sockaddr *)&this->addr, (socklen_t *)&addrlen)) < 0)
            exit(1);

        char buffer[SIZEBUF] = {0};

        read(n, buffer, SIZEBUF);

        printf("%s\n", buffer);

        write(n, hello, strlen(hello));

        close(n);
    }
}

int Host::attach(int sock, struct sockaddr_in addr)
{
    return bind(sock, (struct sockaddr *)&addr, sizeof(addr));
}

Client::Client(u_short domain, int type, int proto, int port, u_long dev)
    : Socket(domain, type, proto, port, dev)
{

    if (this->connection = this->attach(this->sock, this->addr) < 0)
        exit(1);
}

int Client::attach(int sock, struct sockaddr_in addr)
{
    return connect(sock, (struct sockaddr *)&addr, sizeof(addr));
}