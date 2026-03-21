#ifndef STACK_H
#define STACK_H

#include <cstddef>

namespace ods {
    template <typename T>
    class Stack {
    public:
        virtual ~Stack() = default;
        virtual void push(const T& x) = 0;
        virtual T pop() = 0;
        virtual const T& peek() const = 0;
        virtual std::size_t size() const = 0;
        virtual bool empty() const = 0;  
        virtual void clear() = 0;        
    };
}

#endif