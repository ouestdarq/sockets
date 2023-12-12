#pragma once

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