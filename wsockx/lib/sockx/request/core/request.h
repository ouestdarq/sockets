#pragma once

#include <unordered_map>
#include <string_view>
#include <string>

#define BUFFER 30000

#define SAMPLE_HEAD "HTTP/1.1 200 OK\n\n<html>hello world!</html>\n"
#define SAMPLE_REQ "GET / HTTP/1.1\nUser-Agent: nil\nAccept: */*\n\n"

class Request
{
public:
    char *buffer;
    std::unordered_map<std::string_view, std::string_view> line;
    std::unordered_map<std::string_view, std::string_view> head;
    std::unordered_map<std::string_view, std::string_view> body;

public:
    Request(const char *b);
    ~Request();

private:
    void initialize(const char *b);

    void parse_line(char *l);
    void parse_head(char *h);

    int re_validate(const char *index, char *target);
};