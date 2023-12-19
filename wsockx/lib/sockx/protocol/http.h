#pragma once

#include "core/request.h"

class Http : public Request
{
public:
    Http(const char *b);
};