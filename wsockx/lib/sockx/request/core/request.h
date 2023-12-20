#pragma once
#include <validation/regex-validator.h>

#include <unordered_map>
#include <string_view>

#define BUFFER 300

#define SAMPLE_HEAD "HTTP/1.1 200 OK\n\n<html>hello world!</html>\n"
#define SAMPLE_REQ "GET / HTTP/1.1\nUser-Agent: nil\nAccept: */*\n\n"

using dictionary = std::unordered_map<std::string_view, std::string_view>;
using list = std::unordered_map<int, std::string_view>;

class Request
{

public:
    dictionary rl;
    dictionary rh;
    dictionary rb;

private:
    char *buffer;
    char response[BUFFER];
    RegexValidator *validator;

public:
    Request(const char *b);
    ~Request();

private:
    void parse(const char *buffer);
    void set_rh(char *request_header);
    void set_rl(char *request_line);
};