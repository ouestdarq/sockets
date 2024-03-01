#pragma once

#include <unordered_map>
#include <string_view>

using Dictionary = std::unordered_map<std::string_view, std::string_view>;

class RegexValidator
{
protected:
    Dictionary rules;

public:
    RegexValidator(Dictionary rules);

    int validate(const char *entry, char *target);

    const char *rule(const char *entry);
};