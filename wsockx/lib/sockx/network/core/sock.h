#pragma once

#include <netinet/in.h>
#include <sys/socket.h>

#define BUFFER 30000
#define BACKLOG 10

#define HEADERSAMPLE "HTTP/1.1 200 OK\
Content-Type: text/html\
Connection: keep-alive\n\n\
<html>hello world!</html>\
\n"

class Sock
{
protected:
    int sock;
    int connection;
    struct sockaddr_in addr;

public:
    Sock(u_short domain, int type, int proto, int port, u_long dev);

protected:
    virtual int attach(int sock, struct sockaddr_in addr) = 0;
};