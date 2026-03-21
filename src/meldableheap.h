#pragma once
#include "../include/priorityqueue.h"
#include <cstdlib>
#include <stdexcept>

using namespace std;

template <typename T>
class MeldableHeap : public PriorityQueue<T>
{
private:
    struct Node
    {
        T x;
        Node* left;
        Node* right;
        Node* parent;
    };

    Node* nil;
    Node* r;
    size_t n;

    Node* merge(Node* h1, Node* h2)
    {
        if (h1 == nil) return h2;
        if (h2 == nil) return h1;
        if (h1->x > h2->x) return merge(h2, h1);

        if (rand() % 2)
        {
            h1->left = merge(h1->left, h2);
            if (h1->left != nil) h1->left->parent = h1;
        }
        else
        {
            h1->right = merge(h1->right, h2);
            if (h1->right != nil) h1->right->parent = h1;
        }
        return h1;
    }

    void deleteTree(Node* u)
    {
        if (u == nil) return;
        deleteTree(u->left);
        deleteTree(u->right);
        delete u;
    }

public:
    MeldableHeap()
    {
        nil = new Node();
        nil->left = nil->right = nil->parent = nil;
        r = nil;
        n = 0;
    }

    ~MeldableHeap()
    {
        deleteTree(r);
        delete nil;
    }

    bool add(T x) override
    {
        Node* u = new Node();
        u->x = x;
        u->left = u->right = u->parent = nil;
        r = merge(u, r);
        r->parent = nil;
        n++;
        return true;
    }

    T remove() override
    {
        if (isEmpty()) throw out_of_range("Heap is empty");
        T x = r->x;
        Node* tmp = r;
        r = merge(r->left, r->right);
        delete tmp;
        if (r != nil) r->parent = nil;
        n--;
        return x;
    }

    // remove a specific node
    void remove(Node* u)
    {
        if (u == nil) return;
        Node* merged = merge(u->left, u->right);
        if (merged != nil) merged->parent = u->parent;

        if (u->parent == nil)
        {
            r = merged;
        }
        else if (u->parent->left == u)
        {
            u->parent->left = merged;
        }
        else
        {
            u->parent->right = merged;
        }
        delete u;
        n--;
    }

    // absorb all elements of another heap into this one
    void absorb(MeldableHeap<T>& other)
    {
        r = merge(r, other.r);
        if (r != nil) r->parent = nil;
        n += other.n;
        other.r = other.nil;
        other.n = 0;
    }

    T peek() const
    {
        if (isEmpty()) throw out_of_range("Heap is empty");
        return r->x;
    }

    bool isEmpty() const override { return n == 0; }

    size_t size() const override { return n; }
};
