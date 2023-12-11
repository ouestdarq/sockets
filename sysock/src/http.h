#pragma once

typedef enum
{
    CONNECT,
    DELETE,
    GET,
    HEAD,
    OPTIONS,
    PATCH,
    POST,
    PUT,
    TRACE,
} METHODS;

class Http
{
protected:
    const char *uri;
    float version;
    int method;

public:
    Http(char *request);

    int map_methods(const char *m);
};