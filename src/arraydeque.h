#pragma once
#include "../include/array.h"
#include "../include/deque.h"
#include "../include/list.h"
#include <stdexcept>

using namespace std;

template <typename T>
class ArrayDeque : public Deque<T>, public List<T>
{
private:
    array<T> data;
    size_t capacity;
    size_t front;
    size_t count;

    static constexpr size_t MIN_CAPACITY = 4;

    void resize(size_t newCapacity)
    {
        if (newCapacity < MIN_CAPACITY) newCapacity = MIN_CAPACITY;
        array<T> newData(newCapacity);
        for (size_t i = 0; i < count; ++i)
        {
            newData[i] = data[(front + i) % capacity];
        }
        data = newData;
        capacity = newCapacity;
        front = 0;
    }

public:
    ArrayDeque(size_t initCapacity = 10) : data(initCapacity)
    {
        capacity = initCapacity;
        front = 0;
        count = 0;
    }

    // --- Deque<T> methods ---
    void addFirst(const T& x) override
    {
        if (count == capacity) resize(capacity + capacity / 2);
        front = (front + capacity - 1) % capacity;
        data[front] = x;
        ++count;
    }

    void addLast(const T& x) override
    {
        if (count == capacity) resize(capacity + capacity / 2);
        size_t back = (front + count) % capacity;
        data[back] = x;
        ++count;
    }

    T removeFirst() override
    {
        if (isEmpty()) throw out_of_range("Deque is empty");
        T val = data[front];
        front = (front + 1) % capacity;
        --count;
        if (count == 0) front = 0;
        if (count > 0 && count <= capacity / 4 && capacity / 2 >= MIN_CAPACITY)
            resize(capacity / 2);
        return val;
    }

    T removeLast() override
    {
        if (isEmpty()) throw out_of_range("Deque is empty");
        size_t back = (front + count - 1) % capacity;
        T val = data[back];
        --count;
        if (count == 0) front = 0;
        if (count > 0 && count <= capacity / 4 && capacity / 2 >= MIN_CAPACITY)
            resize(capacity / 2);
        return val;
    }

    const T peekFirst() const override
    {
        if (isEmpty()) throw out_of_range("Deque is empty");
        return data[front];
    }

    const T peekLast() const override
    {
        if (isEmpty()) throw out_of_range("Deque is empty");
        size_t back = (front + count - 1) % capacity;
        return data[back];
    }

    bool isEmpty() const override
    {
        return count == 0;
    }

    void clear() override
    {
        count = 0;
        front = 0;
    }

    size_t size() const override
    {
        return count;
    }

    // --- List<T> methods ---
    void add(const size_t i, const T& x) override
    {
        if (i > count) throw out_of_range("Index out of range");
        if (count == capacity) resize(capacity + capacity / 2);

        if (i == 0) {
            addFirst(x);
        } else if (i == count) {
            addLast(x);
        } else if (i < count / 2)
        {
            front = (front + capacity - 1) % capacity;
            for (size_t j = 0; j < i; ++j) {
                size_t src = (front + j + 1) % capacity;
                size_t dst = (front + j) % capacity;
                data[dst] = data[src];
            }
            data[(front + i) % capacity] = x;
            ++count;
        } else {
            for (size_t j = count; j > i; --j) {
                size_t dst = (front + j) % capacity;
                size_t src = (front + j - 1) % capacity;
                data[dst] = data[src];
            }
            data[(front + i) % capacity] = x;
            ++count;
        }
    }

    T remove(const size_t i) override
    {
        if (i >= count) throw out_of_range("Index out of range");

        if (i == 0) {
            return removeFirst();
        } else if (i == count - 1) {
            return removeLast();
        }

        T val = data[(front + i) % capacity];

        if (i < count / 2)
        {
            for (size_t j = i; j > 0; --j) {
                size_t dst = (front + j) % capacity;
                size_t src = (front + j - 1) % capacity;
                data[dst] = data[src];
            }
            front = (front + 1) % capacity;
            --count;
        } else
        {
            for (size_t j = i; j < count - 1; ++j) {
                size_t dst = (front + j) % capacity;
                size_t src = (front + j + 1) % capacity;
                data[dst] = data[src];
            }
            --count;
        }
        if (count > 0 && count <= capacity / 4 && capacity / 2 >= MIN_CAPACITY)
            resize(capacity / 2);
        return val;
    }

    T get(const size_t i) const override
    {
        if (i >= count) throw out_of_range("Index out of range");
        return data[(front + i) % capacity];
    }

    T set(const size_t i, const T& x) override
    {
        if (i >= count) throw out_of_range("Index out of range");
        size_t index = (front + i) % capacity;
        T old = data[index];
        data[index] = x;
        return old;
    }
};
