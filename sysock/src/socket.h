#pragma once

#include <netinet/in.h>
#include <sys/socket.h>

#define SIZEBUF 30000
#define SIZESOC 10

#define HEADERSAMPLE "HTTP/1.1 200 OK\
    Content-Type: text/html\
    Connection: close\n\n\
    <html>hello world!</html>"

typedef struct sockaddr_in addr_t;

class Socket
{
protected:
    int sock;
    int connection;
    addr_t addr;

public:
    Socket(u_short domain, int type, int proto, int port, u_long dev);
    ~Socket();

protected:
    virtual int attach(int sock, addr_t addr) = 0;
};

class Host : public Socket
{
public:
    Host(u_short domain, int type, int proto, int port, u_long dev);

protected:
    int attach(int sock, addr_t addr);
};

class Client : public Socket
{
public:
    Client(u_short domain, int type, int proto, int port, u_long dev);

protected:
    int attach(int sock, addr_t addr);
};
