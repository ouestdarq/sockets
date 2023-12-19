#include <validation/regex-validator.h>

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

int RegexValidator::check(const char *entry, char *target)
{
    const char *regex;
    regex_t re;

    regex = this->get(entry);

    if (regcomp(&re, regex, REG_EXTENDED))
        goto err;

    return !regexec(&re, target, 0, NULL, 0);
err:
    perror("Error compliling regex");
    exit(1);
}

const char *RegexValidator::get(const char *entry)
{
    if (this->m.find(entry) == this->m.end() || this->m[entry].empty())
        goto err;

    return this->m[entry].data();
err:
    perror("Error unable to resolve entry");
    exit(1);
}

RegexValidator::RegexValidator(std::unordered_map<std::string_view, std::string_view> map_re)
{
    this->m = map_re;
}