#pragma once

#include "node.h"

template <typename T>
class BinarySearchTree
{
private:
    Node<T> *head;

public:
    BinarySearchTree() {}

    virtual int compare() = 0;

    void iterate(Node<T> curr, T data, int *direction)
    {
        switch (this->compare(curr->data, data))
        {
        case 0:
            *direction = 0;
            break;
        case 1:
            if (!curr->prev)
                *direction = -1;
            else
                return this->iterate(curr->prev, data, direction);
            break;
        default:
            if (!curr->next)
                *direction = 1;
            else
                return this->iterate(curr->next, data, direction);
            break;
        }
        return curr;
    }

    void insert(T data)
    {
        int *direction;
        Node<T> *node = new Node<T>(data);
        Node<T> *curr = iterate(this->head, data, direction);

        if (*direction < 0)
            curr->prev = node;
        else
            curr->next = node;
    }

    Node<T> *search(T data)
    {
        int *direction;
        Node<T> *curr = this->iterate(this->head, data, direction);

        if (*direction == 0)
            return curr;
        else
            return nullptr;
    }
};