#pragma once
#include "../include/stack.h"
#include <stdexcept>
#include <algorithm>

namespace ods {
    template <typename T>
    class ArrayStack : public Stack<T> {
    private:
        T* a;
        std::size_t n;
        std::size_t capacity;

        void resize() {
            if(capacity == 0) capacity = 1;
            else capacity *= 2;
            
            T* b = new T[capacity];
            for (std::size_t i = 0; i < n; i++) b[i] = a[i];
            delete[] a;
            a = b;
        }

    public:
        ArrayStack() : a(nullptr), n(0), capacity(0) {}
        ~ArrayStack() { delete[] a; }

        void push(const T& x) override {
            if (n + 1 > capacity) resize();
            a[n++] = x;
        }

        T pop() override {
            if (n == 0) throw std::out_of_range("Stack empty");
            return a[--n];
        }

        const T& peek() const override {
            if (n == 0) throw std::out_of_range("Stack empty");
            return a[n - 1];
        }

        std::size_t size() const override { return n; }

        bool empty() const override { return n == 0; }

        void clear() override { n = 0; }
    };
}