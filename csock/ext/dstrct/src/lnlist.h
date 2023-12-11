#pragma once

#include "node.h"

template <typename T>
class LnList
{
protected:
    Node<T> *head;
    int count;

public:
    LnList()
    {
        this->head = nullptr;
        this->count = 0;

        return;
    }

    constexpr T &operator[](int index)
    {
        return this->read(index)->data;
    }

    int size() const
    {
        return this->count;
    }

    Node<T> *read(int index) const
    {
        Node<T> *cursor;
        if (index < 0 || index > this->count)
            goto err;

        cursor = this->head;
        for (int i = 0; i < index; i++)
            cursor = cursor->next;

        return cursor;

    err:
        perror("Error reading Node");
        exit(1);
    }

    void insert(int index, T data)
    {
        Node<T> *node = new Node<T>(data);

        if (!index)
        {
            node->next = this->head;
            this->head = node;
        }
        else
        {
            Node<T> *cursor = this->read(--index);

            node->next = cursor->next;
            cursor->next = node;
        }
        ++this->count;

        return;
    }

    void destroy()
    {
        for (int i = 0; i < this->count; i++)
            this->remove(0);

        return;
    };

    void remove(int index)
    {
        Node<T> *node;
        if (!index)
        {
            node = this->head;
            this->head = node->next;
        }
        else
        {
            Node<T> *cursor = this->read(--index);

            node = cursor->next;
            cursor->next = node->next;
        }
        delete node;
        --this->count;

        return;
    };
};