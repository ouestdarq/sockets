#pragma once
#include <validation/regex-validator.h>

#define BUFFER 300

#define SAMPLE_HEAD "HTTP/1.1 200 OK\n\n<html>hello world!</html>\n"
#define SAMPLE_REQ "GET / HTTP/1.1\nUser-Agent: nil\nAccept: */*\n\n"

using Dictionary = std::unordered_map<std::string_view, std::string_view>;
using List = std::unordered_map<int, std::string_view>;

class Request : public RegexValidator
{
protected:
    char *buffer;
    char response[BUFFER];

    Dictionary rl;
    Dictionary rh;
    Dictionary rb;

    // Validator *validator;

private:
    void parse(const char *buffer);
    void set_rh(char *request_header);
    void set_rl(char *request_line);

public:
    Request(const char *buffer, Dictionary rules);
    ~Request();
};
