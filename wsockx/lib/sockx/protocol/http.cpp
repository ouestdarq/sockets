#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "http.h"

enum METHODS
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
};

dictionary<int> m_http_methods = {
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

void Request::initialize(char **r)
{
    int l = strlen(*r);
    if (!l)
        goto err;
    for (int i = 0; i < l - 2; i++)
        if ((*r)[i] == '\n' &&
            (*r)[i + 2] == '\n')
            (*r)[i + 1] = '|';
    return;
err:
    perror("Error parsing request");
    exit(1);
}

void Request::parse_line(char *l)
{
    this->line["method"] = strtok(l, " ");
    this->line["uri"] = strtok(nullptr, " ");
    this->line["version"] = strtok(nullptr, "/");
    this->line["version"] = strtok(nullptr, "\0");

    return;
}

Request::Request(char *r)
{
    this->initialize(&r);

    char *line = strtok(r, "\n");
    char *head = strtok(nullptr, "|");
    char *body = strtok(nullptr, "|");

    this->parse_line(line);

    return;
err:
    perror("Error parsing request");
    exit(1);
}

Http::Http(char *request) : Request(request)
{
    printf("%i\n", m_http_methods[this->line["method"]]);
    return;
err:
    perror("Error parsing request");
    exit(1);
}