#include <request/protocols/http.h>

#include <stdio.h>

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

static std::unordered_map<std::string_view, int> m_http_methods = {
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

Http::Http(const char *buffer) : Request(buffer)
{
    // for (auto &[k, v] : this->rl)
    //     printf("[%s] = %s\n", k.data(), this->rl[k].data());
    // for (auto &[k, v] : this->rh)
    //     printf("[%s] = %s\n", k.data(), this->rh[k].data());
    return;
}
