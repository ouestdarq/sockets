#include <network/sockets/sock.h>

#include <netinet/in.h>
#include <sys/socket.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Sock::Sock(u_short domain, int type, int proto, int port, u_long dev)
{
    int option = 1;

    this->addr = {
        sin_family : domain,
        sin_port : htons(port),
        sin_addr : {
            s_addr : htonl(dev),
        },
    };

    memset(this->addr.sin_zero, '\0', sizeof(this->addr.sin_zero));

    if ((this->fd = socket(domain, type, proto)) < 0)
        goto err;
    printf("initializing socket\t\t\t...done\n");

    option = setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

    // printf("%i\n", option);

    return;
err:
    shutdown(this->fd, SHUT_RDWR);
    perror("Error initializing socket");
    exit(1);
}