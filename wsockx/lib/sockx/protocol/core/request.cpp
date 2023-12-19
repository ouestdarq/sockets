#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "request.h"

static std::unordered_map<std::string_view, std::string_view> map_req_re = {
    {"body", ""},
    {"head", "^([a-zA-Z]+[-]?)+[:][' '](.+)"},
    {"line", "^([A-Z]+)[' ']([/](.?)+)[' '][A-Z]+[/]([0-9]+[.][0-9]+)"},
};

#define REGEX_LINE
#define REGEX_HEAD

int Request::re_validate(const char *index, char *target)
{
    regex_t re;
    std::string_view regex;

    if (map_req_re.find(index) == map_req_re.end())
        goto err;

    regex = map_req_re[index];

    if (regex.empty())
        goto err;

    return !regcomp(&re, regex.data(), REG_EXTENDED) &&
           !regexec(&re, target, 0, NULL, 0);
err:
    perror("TODO: validator class/injection for reusable purposes (?)");
    exit(1);
}

void Request::parse_head(char *h)
{
    std::unordered_map<int, std::string_view> map_fields;

    int count = 0;
    char *field = strtok(h, "\n");
    do
        map_fields[count++] = field;
    while (field = strtok(NULL, "\n"));

    for (int i = 0; i < count; i++)
    {
        char *key = strtok((char *)map_fields[i].data(), ":");
        char *val = strtok(NULL, " ");
        this->head[key] = val;
    }

    return;
err:
    perror("TODO: handle BAD header");
}

void Request::parse_line(char *l)
{
    if (!this->re_validate("line", l))
        goto err;

    this->line["method"] = strtok(l, " ");
    this->line["uri"] = strtok(NULL, " ");
    this->line["type"] = strtok(NULL, "/");
    this->line["version"] = strtok(NULL, "\0");

    return;
err:
    perror("TODO: handle BAD request_line");
    exit(1);
}

void Request::initialize(const char *b)
{
    int size;
    if (!(size = strlen(b)))
        goto err;

    this->buffer = new char[size + 1];

    memcpy(this->buffer, b, size + 1);

    for (int i = 0; i < size - 2; i++)
        if (this->buffer[i] == '\n' && this->buffer[i + 2] == '\n')
            this->buffer[i + 1] = '|';

    return;
err:
    perror("TODO: handle EMPTY requests");
    exit(1);
}

Request::Request(const char *b)
{
    this->initialize(b);

    char *line = strtok(this->buffer, "\n");
    char *head = strtok(NULL, "|");
    char *body = strtok(NULL, "\n");

    this->parse_line(line);
    // this->parse_head(head);

    return;
}

Request::~Request()
{
    delete this->buffer;
}