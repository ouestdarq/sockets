#include <request/protocols/http.h>

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

Http::Http(const char *b) : Request(b)
{
    // for (auto &[k, v] : this->line)
    //     printf("%s\n", this->line[k].data());
    return;
}
