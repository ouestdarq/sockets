#include <request/core/request.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Dictionary map_rules = {
    {"re_request", "^([a-zA-Z0-9*/=_?.,;:()\"' '-]+\n)+)\n\n.+$"},
    {"re_header", "^([a-zA-Z-]+)([:][' '][a-zA-Z0-9*/=_?.,;:()\"' '-]+)?.{1}$"},
    {"re_request_line", "^([A-Z]+)[' ']([/](.?)+)[' '][A-Z]+[/]([0-9]+[.]?)+.{1}$"},
};

void Request::set_rh(char *h)
{
    char *h_l = strtok(h, "\n");
    int k = 0;
    List m_h = {};
    do
        if (!this->validate("re_header", h_l))
            goto err;
        else
            m_h[k++] = h_l;
    while (h_l = strtok(NULL, "\n"));

    if (k != m_h.size())
        goto err;

    for (auto &[l, m] : m_h)
    {
        char *n = strtok((char *)m.data(), ":");
        this->rh[n] = strtok(NULL, "\n") ?: "";
    }

    return;
err:
    perror("TODO: handle BAD header");
    exit(1);
}

void Request::set_rl(char *l)
{
    if (!this->validate("re_request_line", l))
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
buffer:
    delete this->buffer;
validator:
    delete this;
}

Request::Request(const char *b, Dictionary rules) : RegexValidator(rules)
{
    this->parse(b);

    return;
}