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

Host::Host(u_short domain, int type, int proto, int port, u_long dev)
    : Socket(domain, type, proto, port, dev)
{
    const char *h = HEADERSAMPLE;
    char buffer[SIZEBUF] = {0};
    int addrlen = sizeof(this->addr);
    int conn;

    printf("initializing connection");
    if ((this->connection = this->attach(this->sock, this->addr) < 0))
        goto err;
    printf("\t\t\t...done\n\n");

    printf("...listening (port %i)\n", port);
    if (listen(this->sock, SIZESOC) < 0)
        goto err;

    while (true)
    {
        if ((conn = accept(this->sock, (struct sockaddr *)&this->addr, (socklen_t *)&addrlen)) < 0)
            goto err;

        printf("...reading\n", port);
        read(conn, buffer, SIZEBUF);

        Http http = Http(buffer);

        write(conn, h, strlen(h));

        close(conn);
    }
err:
{
    exit(1);
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