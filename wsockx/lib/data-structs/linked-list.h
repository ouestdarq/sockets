#pragma once

#include "node.h"

template <typename T>
class LinkedList
{
protected:
    Node<T> *head;
    int count;

public:
    LinkedList()
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
        return this->count + 1;
    }

    Node<T> *read(int index) const
    {
        Node<T> *curr;
        if (index < 0 || index > this->count)
            goto err;

        curr = this->head;
        for (int i = 0; i < index; i++)
            curr = curr->next;

        return curr;

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
            Node<T> *curr = this->read(--index);

            node->next = curr->next;
            curr->next = node;
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
        Node<T> *node, *curr;
        if (!index)
        {
            node = this->head;
            this->head = node->next;
        }
        else
        {
            if ((curr = this->read(--index))->next == nullptr)
                goto err;

            node = curr->next;
            curr->next = node->next;
        }
        delete node;
        --this->count;

        return;

    err:
        perror("Error removing Node");
        exit(1);
    };
};