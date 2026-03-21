#pragma once
#include <cstddef>

namespace ods {
template <typename T>
struct PriorityQueue
{
    virtual bool add(T x) = 0;
    virtual T remove() = 0;
    virtual bool isEmpty() const = 0;
    virtual size_t size() const = 0;
};
}