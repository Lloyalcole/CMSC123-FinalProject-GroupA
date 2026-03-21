#pragma once

namespace ods {
template <typename T>
struct uset 
{
    virtual void add(T x) = 0;
    virtual void remove(T x) = 0;
    virtual bool contains(T x) = 0;
    virtual ~uset() {}
};
}