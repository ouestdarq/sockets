#include <request/core/request.h>

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Request::set_rh(char *h)
{
    std::unordered_map<int, std::string_view> map_head;

    int count = 0;
    char *head_line = strtok(h, "\n");
    do
        if (!this->validator->check("header_line", head_line))
            goto err;
        else
            map_head[count++] = head_line;
    while (head_line = strtok(NULL, "\n"));
    printf("%i\n", map_head.size());
    for (int i = 0; i < count; i++)
    {
        char *current = (char *)map_head[i].data();
        char *key = strtok(current, ":");
        char *val = strtok(NULL, "\n");
        this->rh[key] = val ?: "";
    }

    return;
err:
    perror("TODO: handle BAD header");
    exit(1);
}

void Request::set_rl(char *l)
{
    if (!this->validator->check("request_line", l))
        goto err;

    this->rl["method"] = strtok(l, " ");
    this->rl["uri"] = strtok(NULL, " ");
    this->rl["type"] = strtok(NULL, "/");
    this->rl["version"] = strtok(NULL, "\0");

    return;
err:
    perror("TODO: handle BAD request_line");
    exit(1);
}

void Request::parse(const char *b)
{
    char *rb, *rh, *rl;
    int size;

    if (!(size = strlen(b)))
        goto err;

    this->buffer = new char[size + 1];

    memcpy(this->buffer, b, size + 1);

    for (int i = 0; i < size - 2; i++)
        if (this->buffer[i] == '\n' && this->buffer[i + 2] == '\n')
            this->buffer[i + 1] = '|';

    rl = strtok(this->buffer, "\n");
    rh = strtok(NULL, "|");
    rb = strtok(NULL, "\n");

    this->set_rl(rl);
    this->set_rh(rh);

    return;
err:
    perror("TODO: handle EMPTY requests");
    exit(1);
}

Request::~Request()
{
    delete this->buffer, this->validator;
}

Request::Request(const char *b)
{
    this->validator = new RegexValidator(map_regex_request);

    this->parse(b);

    return;
}
