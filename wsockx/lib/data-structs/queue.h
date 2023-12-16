#pragma once

#include "linked-list.h"

template <typename T>
class Queue : private LinkedList<T>
{
public:
    constexpr T &operator[](int index)
    {
        return this->read(index)->data;
    }

    int size() const
    {
        return this->count;
    }

    T pop()
    {
        T data = this->read(0)->data;
        this->remove(0);

        return data;
    }

    void push(T data)
    {
        this->insert(this->count, data);

        return;
    }
};
