#include <validation/regex-validator.h>

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

int RegexValidator::validate(const char *entry, char *target)
{
    const char *regex;
    regex_t re;

    if ((regex = this->rule(entry)) == NULL || regcomp(&re, regex, REG_EXTENDED))
        goto err;

    return !regexec(&re, target, 0, NULL, 0);
err:
    perror("Error compliling regex\n");
    return -1;
}

const char *RegexValidator::rule(const char *entry)
{
    if (this->rules.find(entry) == this->rules.end() || this->rules[entry].empty())
        goto err;

    return this->rules[entry].data();
err:
    perror("Error unable to resolve entry\n");
    return NULL;
}

RegexValidator::RegexValidator(Dictionary rules)
{
    this->rules = rules;
}