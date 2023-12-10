#pragma once

struct strcmp_s
{
    bool operator()(char const *s1, char const *s2) const
    {
        return strcmp(s1, s2) < 0;
    }
};

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
