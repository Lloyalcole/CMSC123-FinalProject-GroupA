#pragma once
#include <cstddef>
#include <stdexcept>

using namespace std;

template <typename T>
class SLListQueue
{
private:
    struct Node
    {
        T data;
        Node* next;

        Node(const T& x) : data(x), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t count;

public:
    SLListQueue()
    {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    ~SLListQueue()
    {
        clear();
    }

    void enqueue(const T& x)
    {
        Node* u = new Node(x);

        if (count == 0)
        {
            head = u;
            tail = u;
        }
        else
        {
            tail->next = u;
            tail = u;
        }

        ++count;
    }

    T dequeue()
    {
        if (isEmpty()) throw out_of_range("Queue is empty");

        Node* u = head;
        T val = u->data;

        head = head->next;
        delete u;
        --count;

        if (count == 0)
        {
            tail = nullptr;
        }

        return val;
    }

    T front() const
    {
        if (isEmpty()) throw out_of_range("Queue is empty");
        return head->data;
    }

    bool isEmpty() const
    {
        return count == 0;
    }

    size_t size() const
    {
        return count;
    }

    void clear()
    {
        while (head != nullptr)
        {
            Node* next = head->next;
            delete head;
            head = next;
        }

        tail = nullptr;
        count = 0;
    }
};