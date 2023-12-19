#pragma once
#include <validation/regex-validator.h>

#include <unordered_map>
#include <string_view>

#define BUFFER 300

#define SAMPLE_HEAD "HTTP/1.1 200 OK\n\n<html>hello world!</html>\n"
#define SAMPLE_REQ "GET / HTTP/1.1\nUser-Agent: nil\nAccept: */*\n\n"

static std::unordered_map<std::string_view, std::string_view> map_regex_request = {
    {"body", ""},
    {"header_line", "^([a-zA-Z]+[-]?)+[:]?[' ']?(.+)"},
    {"request_line", "^([A-Z]+)[' ']([/](.?)+)[' '][A-Z]+[/]([0-9]+[.][0-9]+)"},
};

class Request
{
public:
    std::unordered_map<std::string_view, std::string_view> rl;
    std::unordered_map<std::string_view, std::string_view> rh;
    std::unordered_map<std::string_view, std::string_view> rb;

private:
    char *buffer;
    RegexValidator *validator;

public:
    Request(const char *b);
    ~Request();

private:
    void parse(const char *buffer);
    void set_rh(char *request_header);
    void set_rl(char *request_line);
};