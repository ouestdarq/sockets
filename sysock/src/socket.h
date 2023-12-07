#pragma once

#include <netinet/in.h>
#include <sys/socket.h>

#define SIZEBUF 30000
#define SIZESOC 10

class Socket
{
protected:
    int sock;
    int connection;
    struct sockaddr_in addr;

public:
    Socket(u_short domain, int type, int proto, int port, u_long dev);

protected:
    virtual int attach(int sock, struct sockaddr_in addr) = 0;
};

class Host : public Socket
{
public:
    Host(u_short domain, int type, int proto, int port, u_long dev);

protected:
    int attach(int sock, struct sockaddr_in addr);
};

class Client : public Socket
{
public:
    Client(u_short domain, int type, int proto, int port, u_long dev);

protected:
    int attach(int sock, struct sockaddr_in addr);
};