#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <protocol/http.h>

#include "host.h"

int Host::attach(int sock, struct sockaddr_in addr)
{
    return bind(sock, (struct sockaddr *)&addr, sizeof(addr));
}

void Host::run()
{
    const char *h = HEADERSAMPLE;
    char buffer[BUFFER] = {0};
    int addrlen = sizeof(this->addr);
    int conn;

    while (true)
    {
        if ((conn = accept(this->sock, (struct sockaddr *)&this->addr, (socklen_t *)&addrlen)) < 0)
            goto err;

        if (recv(conn, buffer, BUFFER, 0) < 0)
            goto err;

        Http http = Http(buffer);

        if (send(conn, h, strlen(h), 0) < 0)
            goto err;

        shutdown(conn, SHUT_RDWR);
    }
    return;
err:
    perror("Error: could not read/write incoming");
    exit(1);
}

Host::Host(u_short domain, int type, int proto, int port, u_long dev)
    : Sock(domain, type, proto, port, dev)
{
    if ((this->connection = this->attach(this->sock, this->addr) < 0))
        goto err;
    printf("initializing connection\t\t\t...done\n");

    if (listen(this->sock, BACKLOG) < 0)
        goto err;
    printf("listening on port :%i\t\t\t...done\n", port);

    this->run();

    return;

err:
    perror("Error: could not initialize Host");
    exit(1);
}