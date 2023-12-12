#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <requests/http.h>
#include "host.h"

int Host::attach(int sock, struct sockaddr_in addr)
{
    return bind(sock, (struct sockaddr *)&addr, sizeof(addr));
}

Host::Host(u_short domain, int type, int proto, int port, u_long dev)
    : Sock(domain, type, proto, port, dev)
{
    printf("initializing connection");
    if ((this->connection = this->attach(this->sock, this->addr) < 0))
        goto err;
    printf("\t\t\t...done\n");

    printf("listening");
    if (listen(this->sock, BACKLOG) < 0)
        goto err;
    printf("\t\t\t\t...done\n");

    {
        const char *h = HEADERSAMPLE;
        char buffer[BUFFER] = {0};
        int addrlen = sizeof(this->addr);
        int conn;

        while (true)
        {
            if ((conn = accept(this->sock, (struct sockaddr *)&this->addr, (socklen_t *)&addrlen)) < 0)
                goto err;

            if (read(conn, buffer, BUFFER) < 0)
                goto err;

            Http http = Http(buffer);

            if (write(conn, h, strlen(h)) < 0)
                goto err;

            close(conn);
        }
    }

    return;

err:
    perror("\nError: could not initialize Host");
    exit(1);
}