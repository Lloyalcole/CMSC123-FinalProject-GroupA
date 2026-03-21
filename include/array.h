#pragma once

#include <cassert>
#include <cstddef>

namespace ods {

template <typename T>
struct array
{
    size_t length;
    T* a;

    array(size_t n) : length(n), a(nullptr)
    {
        a = new T[n];
    }

    ~array()
    {
        if (a != nullptr)
        {
            delete[] a;
        }
    }

    T& operator[](size_t i)
    {
        assert(i >= 0 && i < length);
        return a[i];
    }

    const T& operator[](size_t i) const
    {
        assert(i >= 0 && i < length);
        return a[i];
    }

    array<T>& operator=(array<T>& other)
    {
        if (this != &other)
        {
            if (a != nullptr)
            {
                delete[] a;
            }
            
            a = other.a;
            length = other.length;

            other.a = nullptr;
            other.length = 0;
        }
        return *this;
    }

private:
    array(const array<T>& other) = delete;
};

} 