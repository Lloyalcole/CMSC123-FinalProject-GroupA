#pragma once
#include "../include/sset.h"
#include <vector>
#include <cstdlib>

namespace ods {
    template <typename T>
    class SkipList : public sset<T> {
    private:
        struct Node {
            T data;
            std::vector<Node*> next;
            Node(T val, int level) : data(val), next(level, nullptr) {}
        };

        Node* head;
        int maxLevel;
        int currentLevel;

    public:
        SkipList() : maxLevel(16), currentLevel(1) {
            head = new Node(T(), maxLevel);
        }

        void add(T x) override {
            std::vector<Node*> update(maxLevel, nullptr);
            Node* temp = head;

            for (int i = currentLevel - 1; i >= 0; i--) {
                while (temp->next[i] != nullptr && temp->next[i]->data < x) {
                    temp = temp->next[i];
                }
                update[i] = temp;
            }

            int lvl = 1;
            while (std::rand() % 2 == 0 && lvl < maxLevel) lvl++;

            if (lvl > currentLevel) {
                for (int i = currentLevel; i < lvl; i++) update[i] = head;
                currentLevel = lvl;
            }

            Node* newNode = new Node(x, lvl);
            for (int i = 0; i < lvl; i++) {
                newNode->next[i] = update[i]->next[i];
                update[i]->next[i] = newNode;
            }
        }

        void remove(T x) override {
            std::vector<Node*> update(maxLevel, nullptr);
            Node* temp = head;
            for (int i = currentLevel - 1; i >= 0; i--) {
                while (temp->next[i] != nullptr && temp->next[i]->data < x) temp = temp->next[i];
                update[i] = temp;
            }
            temp = temp->next[0];
            if (temp != nullptr && temp->data == x) {
                for (int i = 0; i < currentLevel; i++) {
                    if (update[i]->next[i] != temp) break;
                    update[i]->next[i] = temp->next[i];
                }
                delete temp;
            }
        }

        bool contains(T x) override {
            Node* temp = head;
            for (int i = currentLevel - 1; i >= 0; i--) {
                while (temp->next[i] != nullptr && temp->next[i]->data < x) temp = temp->next[i];
            }
            temp = temp->next[0];
            return (temp != nullptr && temp->data == x);
        }
    };
}