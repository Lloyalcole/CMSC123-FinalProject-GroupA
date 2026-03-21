#pragma once

#include "../include/graph.h"
#include <iostream>
#include <vector>
#include <algorithm>

namespace ods {

enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node *left, *right, *parent;
    std::size_t index; 

    Node(int data, std::size_t idx) : data(data), color(RED), 
        left(nullptr), right(nullptr), parent(nullptr), index(idx) {}
};

class RedBlackTree : public Graph {
private:
    Node* root;
    std::vector<Node*> nodes; 

    void rotateLeft(Node*& pt) {
        Node* pt_right = pt->right;
        pt->right = pt_right->left;

        if (pt->right != nullptr)
            pt->right->parent = pt;

        pt_right->parent = pt->parent;

        if (pt->parent == nullptr)
            root = pt_right;
        else if (pt == pt->parent->left)
            pt->parent->left = pt_right;
        else
            pt->parent->right = pt_right;

        pt_right->left = pt;
        pt->parent = pt_right;
    }

    void rotateRight(Node*& pt) {
        Node* pt_left = pt->left;
        pt->left = pt_left->right;

        if (pt->left != nullptr)
            pt->left->parent = pt;

        pt_left->parent = pt->parent;

        if (pt->parent == nullptr)
            root = pt_left;
        else if (pt == pt->parent->left)
            pt->parent->left = pt_left;
        else
            pt->parent->right = pt_left;

        pt_left->right = pt;
        pt->parent = pt_left;
    }

    void fixViolation(Node*& pt) {
        Node* parent_pt = nullptr;
        Node* grand_parent_pt = nullptr;

        while ((pt != root) && (pt->color != BLACK) && (pt->parent->color == RED)) {
            parent_pt = pt->parent;
            grand_parent_pt = pt->parent->parent;

            // Case A: Parent of pt is left child of Grandparent
            if (parent_pt == grand_parent_pt->left) {
                Node* uncle_pt = grand_parent_pt->right;

                // Case 1: Uncle is also RED (Recolor only)
                if (uncle_pt != nullptr && uncle_pt->color == RED) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                } else {
                    // Case 2: pt is right child (Left Rotation needed)
                    if (pt == parent_pt->right) {
                        rotateLeft(parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }
                    // Case 3: pt is left child (Right Rotation needed)
                    rotateRight(grand_parent_pt);
                    std::swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            } 
            // Case B: Parent of pt is right child of Grandparent
            else {
                Node* uncle_pt = grand_parent_pt->left;
                if ((uncle_pt != nullptr) && (uncle_pt->color == RED)) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                } else {
                    if (pt == parent_pt->left) {
                        rotateRight(parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }
                    rotateLeft(grand_parent_pt);
                    std::swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            }
        }
        root->color = BLACK;
    }

public:
    RedBlackTree() : root(nullptr) {}

    std::size_t numVertices() const override { return nodes.size(); }
    
    std::size_t numEdges() const override { 
        return (nodes.size() > 1) ? nodes.size() - 1 : 0; 
    }

    bool hasEdge(std::size_t u, std::size_t v) const override {
        if (u >= nodes.size() || v >= nodes.size()) return false;
        return (nodes[u]->left == nodes[v] || nodes[u]->right == nodes[v]);
    }

    double edgeWeight(std::size_t u, std::size_t v) const override {
        return hasEdge(u, v) ? 1.0 : 0.0;
    }

    void addEdge(std::size_t u, std::size_t v, double weight = 1.0) override {
        std::cout << "Direct edge addition is not allowed in a Red-Black Tree.\n";
    }

    void removeEdge(std::size_t u, std::size_t v) override {
        std::cout << "Direct edge removal is not allowed in a Red-Black Tree.\n";
    }

    std::size_t addVertex() override {
        std::cout << "Use insertValue(int) to add data to the Red-Black Tree.\n";
        return 0;
    }

    void insertValue(int data) {
        Node* node = new Node(data, nodes.size());
        nodes.push_back(node);

        if (root == nullptr) {
            node->color = BLACK;
            root = node;
        } else {
            Node* temp = root;
            Node* parent = nullptr;
            while (temp != nullptr) {
                parent = temp;
                if (node->data < temp->data) temp = temp->left;
                else temp = temp->right;
            }
            node->parent = parent;
            if (node->data < parent->data) parent->left = node;
            else parent->right = node;

            fixViolation(node);
        }
    }

    void removeVertex(std::size_t v) override {
        std::cout << "Standard RBT removal is complex; vertex removal by index not implemented.\n";
    }

    std::vector<std::size_t> neighbours(std::size_t u) const override {
        std::vector<std::size_t> n;
        if (u < nodes.size()) {
            if (nodes[u]->left) n.push_back(nodes[u]->left->index);
            if (nodes[u]->right) n.push_back(nodes[u]->right->index);
        }
        return n;
    }

    std::size_t inDegree(std::size_t v) const override {
        if (v >= nodes.size()) return 0;
        return (nodes[v] == root) ? 0 : 1;
    }

    std::size_t outDegree(std::size_t v) const override {
        return neighbours(v).size();
    }

    void forEachEdge(std::function<void(std::size_t, std::size_t, double)> f) const override {
        for (auto node : nodes) {
            if (node->left) f(node->index, node->left->index, 1.0);
            if (node->right) f(node->index, node->right->index, 1.0);
        }
    }
};

}