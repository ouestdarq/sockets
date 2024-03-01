#include <network/servers/host.h>

#include <request/protocols/http.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int Host::attach(int fd, struct sockaddr_in addr)
{
    return bind(fd, (struct sockaddr *)&addr, sizeof(addr));
}

void Host::run()
{
    char buffer[BUFFER] = {0};

    int client;
    int size_addr = sizeof(this->addr);
    while (true)
    {
        if ((client = accept(this->fd, (struct sockaddr *)&this->addr, (socklen_t *)&size_addr)) < 0)
            goto err;

        if (recv(client, buffer, BUFFER, 0) < 0)
            goto err;

        Http response = buffer;

        memset(buffer, '\0', BUFFER);

        if (send(client, SAMPLE_HEAD, strlen(SAMPLE_HEAD), 0) < 0)
            goto err;

        if (shutdown(client, SHUT_RDWR) < 0)
            goto err;
    }

    return;
err:
    perror("Error completing request");
    exit(1);
}

Host::Host(u_short domain, int type, int proto, int port, u_long dev)
    : Sock(domain, type, proto, port, dev)
{
    if ((this->conn = this->attach(this->fd, this->addr) < 0))
        goto err;
    printf("initializing connection\t\t\t...done\n");

    if (listen(this->fd, BACKLOG) < 0)
        goto err;
    printf("listening on port :%i\t\t\t...done\n", port);

    this->run();

    return;

err:
    perror("Error initializing Host");
    exit(1);
}