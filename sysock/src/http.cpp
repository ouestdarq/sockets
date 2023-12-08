#include <stdio.h>
#include <string.h>
#include <map>

#include "http.h"

using std::map;

Http::Http(char *request)
{
    for (int i = 0; i < strlen(request) - 2; i++)
        if (request[i] == '\n' == request[i + 1])
            request[i + 1] = '|';

    char *line = strtok(request, "\n");
    char *headf = strtok(__null, "|");
    char *body = strtok(__null, "|");

    printf("%s", headf);

    char *method = strtok(line, " ");

    this->method = this->map_method(method);
    this->uri = strtok(__null, " ");
    this->version = strtok(__null, " ");
}

int Http::map_method(char *method)
{
    map<const char *, int> methods = {
        {"GET", GET},
        {"POST", POST},
        {"PUT", PUT},
        {"HEAD", HEAD},
        {"PATCH", PATCH},
        {"DELETE", DELETE},
        {"CONNECT", CONNECT},
        {"OPTIONS", OPTIONS},
        {"TRACE", TRACE},
    };
    return methods[method];
}