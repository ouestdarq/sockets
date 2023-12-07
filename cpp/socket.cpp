#include "socket.h"

Proxymurder::Socket::Socket(u_short domain, int type, int proto, int port, u_long dev)
{
    this->address = {
        sin_family : domain,
        sin_port : htons(port),
        sin_addr : {
            s_addr : htonl(dev),
        },
    };
    if (this->sock = socket(domain, type, proto) < 0)
        goto err;

err:
    exit(1);
}

Proxymurder::Host::Host(u_short domain, int type, int proto, int port, u_long dev)
    : Socket(domain, type, proto, port, dev)
{

    if (this->connection = this->attach(this->sock, this->address) < 0)
        goto err;
err:
    exit(1);
}

int Proxymurder::Host::attach(int sock, struct sockaddr_in address)
{
    return bind(sock, (struct sockaddr *)&address, sizeof(address));
}

int Proxymurder::Client::attach(int sock, struct sockaddr_in address)
{
    return connect(sock, (struct sockaddr *)&address, sizeof(address));
}