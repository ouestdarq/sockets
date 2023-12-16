#pragma once

#include <unordered_map>
#include <string_view>

template <typename T>
using dictionary = std::unordered_map<std::string_view, T>;

class Request
{
protected:
    dictionary<std::string_view> line;
    dictionary<std::string_view> head;
    dictionary<std::string_view> body;

public:
    Request(char *r);

private:
    void initialize(char **r);
    void parse_line(char *l);
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