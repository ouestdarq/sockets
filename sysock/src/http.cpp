#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <map>

#include "http.h"

using std::map;

struct StrCmp
{
    bool operator()(char const *a, char const *b) const
    {
        return strcmp(a, b) < 0;
    }
};

Http::Http(char *request)
{
    char *l, *h, *k, *m, *p, *t, *v;

    if (!strlen(request))
        goto err;

    for (int i = 0; i < strlen(request) - 1; i++)
        if (request[i] == '\n' && request[i + 1] == '\n')
            request[i + 1] = '|';

    l = strtok(request, "\n");
    h = strtok(nullptr, "|");
    k = strtok(nullptr, "|");

    m = strtok(l, " ");
    p = strtok(nullptr, " ");
    t = strtok(nullptr, " ");
    v = strtok(t, "HTTP/");

    this->uri = p;
    this->version = atof(v);
    this->method = this->map_methods(m);

    printf("%s\t%f\t%i\n", this->uri, this->version, this->method);

    return;
err:
    perror("Error parsing request");
    exit(1);
}

int Http::map_methods(const char *m)
{
    map<const char *, int, StrCmp> methods = {
        {"CONNECT", CONNECT},
        {"DELETE", DELETE},
        {"GET", GET},
        {"HEAD", HEAD},
        {"OPTIONS", OPTIONS},
        {"PATCH", PATCH},
        {"POST", POST},
        {"PUT", PUT},
        {"TRACE", TRACE},
    };

    return methods[m];
}