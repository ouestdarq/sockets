#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "http.h"
#include "socket.h"

Socket::Socket(u_short domain, int type, int proto, int port, u_long dev)
{
    this->addr = {
        sin_family : domain,
        sin_port : htons(port),
        sin_addr : {
            s_addr : htonl(dev),
        },
    };
    memset(this->addr.sin_zero, '\0', sizeof(this->addr.sin_zero));

    printf("initializing socket");
    if ((this->sock = socket(domain, type, proto)) < 0)
        exit(1);
    printf("\t\t\t...done\n");
}

Socket::~Socket()
{
    printf("socket terminated...\n\n");
}

Host::Host(u_short domain, int type, int proto, int port, u_long dev)
    : Socket(domain, type, proto, port, dev)
{
    // Look into the different type of headers and if h should be an arg.
    const char *h = HEADERSAMPLE;

    int l = sizeof(this->addr);
    int n;
    int r;

    printf("initializing connection");
    if ((this->connection = this->attach(this->sock, this->addr)) < 0)
        exit(1);
    printf("\t\t\t...listening\n");
    if (listen(this->sock, SIZESOC) < 0)
        exit(1);

    while (true)
    {
        printf("...awaiting connection\n");
        n = accept(this->sock, (struct sockaddr *)&this->addr, (socklen_t *)&l);
        if (n < 0)
            exit(1);

        char buffer[SIZEBUF] = {0};

        read(n, buffer, SIZEBUF);

        Http http = Http(buffer);

        write(n, h, strlen(h));

        close(n);
    }
}

int Host::attach(int sock, addr_t addr)
{
    return bind(sock, (struct sockaddr *)&addr, sizeof(addr));
}

Client::Client(u_short domain, int type, int proto, int port, u_long dev)
    : Socket(domain, type, proto, port, dev)
{

    if (this->connection = this->attach(this->sock, this->addr) < 0)
        exit(1);
}

int Client::attach(int sock, addr_t addr)
{
    return connect(sock, (struct sockaddr *)&addr, sizeof(addr));
}