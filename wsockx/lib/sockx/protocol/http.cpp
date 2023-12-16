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

int Request::initialize(char **r)
{
    int l = strlen(*r);
    if (!l)
        goto err;
    for (int i = 0; i < l - 2; i++)
        if ((*r)[i] == '\n' &&
            (*r)[i + 2] == '\n')
            (*r)[i + 1] = '|';

    return l;
err:
    perror("Error parsing request");
    exit(1);
}

void Request::parse_line(char *l)
{
    int lenght;
    char line[lenght = strlen(l)];

    memcpy(line, l, lenght);

    {
        this->line["method"] = strtok(line, " ");
        this->line["uri"] = strtok(nullptr, " ");
        this->line["version"] = strtok(nullptr, "/");
        this->line["version"] = strtok(nullptr, "\0");
    }

    return;
}

void Request::parse_head(char *h)
{
    int lenght;
    char head[lenght = strlen(h)];
    queue<std::string> m_fields;

    memcpy(head, h, lenght);

    int i = 0;
    char *field = strtok(head, "\n");
    while (field)
    {
        m_fields[i++] = field;
        field = strtok(nullptr, "\n");
    }

    for (int i = 0; i < m_fields.size(); i++)
    {
        char entry[m_fields[i].size() + 1];

        memcpy(entry, m_fields[i].data(), m_fields[i].size() + 1);

        char *key = strtok(entry, ":");
        char *value = strtok(nullptr, " ");

        this->head[key] = value;
        // printf("%s\n", this->head[key].data());
    }

    // printf("%s\n\n", head);
    // this->head["method"] = strtok(head, " ");
    // this->head["uri"] = strtok(nullptr, " ");
    // this->head["version"] = strtok(nullptr, "/");
    // this->head["version"] = strtok(nullptr, "\0");

    return;
}

Request::Request(char *r)
{
    int lenght;
    char request[lenght = this->initialize(&r)];

    memcpy(request, r, lenght);

    char *line = strtok(request, "\n");
    char *head = strtok(nullptr, "|");
    char *body = strtok(nullptr, "\n");

    this->parse_line(line);
    this->parse_head(head);
    // printf("%s\n", head);

    return;
err:
    perror("Error parsing request");
    exit(1);
}

Http::Http(char *r) : Request(r)
{
    printf("%i\n", m_http_methods[this->line["method"]]);
    for (const auto &[k, v] : this->head)
    {
        printf("%s\t%s\n", k.data(), v.data());
    }
    return;
err:
    perror("Error parsing request");
    exit(1);
}