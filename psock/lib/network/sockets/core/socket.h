#pragma once

#define BUFFER 300000
#define BACKLOG 100000

#define HEADERSAMPLE "HTTP/1.1 200 OK\
Content-Type: text/html\
Connection: keep-alive\n\n\
<html>hello world!</html>\
\n"

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