#pragma once

typedef enum
{
    GET,
    POST,
    PUT,
    HEAD,
    PATCH,
    DELETE,
    CONNECT,
    OPTIONS,
    TRACE,
} HTTPMETHODS;

class Http
{
protected:
    int method;
    char *uri;
    char *version;

public:
    Http(char *request);
    int map_method(char *method);
};
