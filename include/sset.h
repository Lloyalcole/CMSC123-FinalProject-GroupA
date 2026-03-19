#pragma once

template <typename T>
struct sset 
{
    virtual void add(T x) = 0;
    virtual void remove(T x) = 0;
    virtual bool contains(T x) = 0;
    virtual ~sset() {}
};