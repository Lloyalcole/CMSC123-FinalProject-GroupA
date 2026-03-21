#pragma once
#include "../include/list.h"
#include <cstddef>
#include <stdexcept>

using namespace std;

template <typename T>
class DLList : public List<T>
{
private:
    struct Node
    {
        T data;
        Node* prev;
        Node* next;

        Node() : prev(nullptr), next(nullptr) {}
        Node(const T& x) : data(x), prev(nullptr), next(nullptr) {}
    };

    Node dummy;
    size_t count;

    Node* getNode(size_t i) const
    {
        if (i >= count) throw out_of_range("Index out of range");

        Node* p;

        if (i < count / 2)
        {
            p = dummy.next;
            for (size_t j = 0; j < i; ++j)
            {
                p = p->next;
            }
        }
        else
        {
            p = dummy.prev;
            for (size_t j = count - 1; j > i; --j)
            {
                p = p->prev;
            }
        }

        return p;
    }

    void addBefore(Node* w, const T& x)
    {
        Node* u = new Node(x);

        u->prev = w->prev;
        u->next = w;

        w->prev->next = u;
        w->prev = u;

        ++count;
    }

    T removeNode(Node* w)
    {
        T val = w->data;

        w->prev->next = w->next;
        w->next->prev = w->prev;

        delete w;
        --count;

        return val;
    }

public:
    DLList()
    {
        dummy.next = &dummy;
        dummy.prev = &dummy;
        count = 0;
    }

    ~DLList()
    {
        clear();
    }

    void clear()
    {
        while (count > 0)
        {
            remove(0);
        }
    }

    void add(const size_t i, const T& x) override
    {
        if (i > count) throw out_of_range("Index out of range");

        if (i == count)
        {
            addBefore(&dummy, x);
        }
        else
        {
            addBefore(getNode(i), x);
        }
    }

    T remove(const size_t i) override
    {
        return removeNode(getNode(i));
    }

    T get(const size_t i) const override
    {
        return getNode(i)->data;
    }

    T set(const size_t i, const T& x) override
    {
        Node* u = getNode(i);
        T old = u->data;
        u->data = x;
        return old;
    }

    size_t size() const override
    {
        return count;
    }
};