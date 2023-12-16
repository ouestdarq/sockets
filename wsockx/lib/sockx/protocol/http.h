#pragma once

#include <unordered_map>
#include <string_view>
#include <string>

template <typename T, typename S = std::string_view>
using dict = std::unordered_map<S, T>;

class Request
{
protected:
    dict<std::string_view> line;
    dict<std::string, std::string> head;
    dict<std::string_view> body;

public:
    Request(char *r);

private:
    int initialize(char **r);
    void parse_line(char *l);
    void parse_head(char *h);
};

class Http : public Request
{
protected:
    // const char *uri;
    // float version;
    // int method;

public:
    Http(char *request);
};