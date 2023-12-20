#include <request/core/request.h>

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static dictionary map_regex_request = {
    {"re_header", "^([a-zA-Z-]+)([:][' '][a-zA-Z0-9*/=_?.,;:()\"' '-]+)?.{1}$"},
    {"re_request", "^([A-Z]+)[' ']([/](.?)+)[' '][A-Z]+[/]([0-9]+[.]?)+.{1}$"},
};

void Request::set_rh(char *h)
{
    list map_head;

    int count = 0;
    char *head_line = strtok(h, "\n");

    do
        if (!this->validator->check("header_line", head_line))
            goto err;
        else
            map_head[count++] = head_line;
    while (head_line = strtok(NULL, "\n"));

    for (int i = 0; i < count; i++)
        this->rh[strtok((char *)map_head[i].data(), ":")] = strtok(NULL, "\n") ?: "";

    return;
err:
    perror("TODO: handle BAD header");
    exit(1);
}

void Request::set_rl(char *l)
{
    if (!this->validator->check("re_reque", l))
        goto err;
    else
        this->rl = {
            {"method", strtok(l, " ")},
            {"uri", strtok(NULL, " ")},
            {"type", strtok(NULL, "/")},
            {"version", strtok(NULL, "\0")},
        };

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
buff:
    delete this->buffer;
validator:
    delete this->validator;
}

Request::Request(const char *b)
{
    this->validator = new RegexValidator(map_regex_request);

    this->parse(b);

    return;
}
