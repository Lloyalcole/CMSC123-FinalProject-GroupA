#pragma once
#include "../include/uset.h"
#include <vector>
#include <list>
#include <cmath>

namespace ods {
    template <typename T>
    class ChainedHashTable : public uset<T> {
    private:
        std::vector<std::list<T>> table;
        std::size_t n;
        std::size_t capacity;

        std::size_t getHash(T x) {
            return std::abs((int)x) % capacity;
        }

    public:
        ChainedHashTable(std::size_t size = 101) : n(0), capacity(size) {
            table.resize(capacity);
        }

        void add(T x) override {
            if (contains(x)) return;
            table[getHash(x)].push_back(x);
            n++;
        }

        void remove(T x) override {
            int h = getHash(x);
            auto& bucket = table[h];
            for (auto it = bucket.begin(); it != bucket.end(); ++it) {
                if (*it == x) {
                    bucket.erase(it);
                    n--;
                    return;
                }
            }
        }

        bool contains(T x) override {
            for (const auto& item : table[getHash(x)]) {
                if (item == x) return true;
            }
            return false;
        }
    };
}