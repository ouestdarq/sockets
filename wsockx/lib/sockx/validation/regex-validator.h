#pragma once

#include <unordered_map>
#include <string_view>

class RegexValidator
{
private:
    std::unordered_map<std::string_view, std::string_view> m;

public:
    RegexValidator(std::unordered_map<std::string_view, std::string_view> map_re);

    int check(const char *e, char *t);

    const char *get(const char *e);
};