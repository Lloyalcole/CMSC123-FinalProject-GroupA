#include "../src/redblacktrees.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace ods;

/*
    Helper to print or visualize the tree with values
    Using a recursive approach to print branches.
*/
void printTreeHelper(Node* root, string indent, bool last) {
    if (root != nullptr) {
        cout << indent;
        if (last) {
            cout << "R----";
            indent += "     ";
        } else {
            cout << "L----";
            indent += "|    ";
        }
        
        // Visualize the color and the data
        string sColor = (root->color == RED) ? "RED" : "BLACK";
        cout << root->data << " (" << sColor << ") [Idx:" << root->index << "]" << endl;
        
        printTreeHelper(root->left, indent, false);
        printTreeHelper(root->right, indent, true);
    }
}

void displayVisualTree(RedBlackTree& rbt) {    
    cout << "\n--- Visual Tree Diagram ---" << endl;
    if (rbt.numVertices() == 0) {
        cout << "[Empty Tree]" << endl;
    } else {
        cout << "Root is the top-most node." << endl;
    }
}

int main() {
    RedBlackTree rbt;
    int choice;
    int value;

    while (true) {
        cout << "\n===============================" << endl;
        cout << "   RED-BLACK TREE GRAPH TESTER " << endl;
        cout << "===============================" << endl;
        cout << "1. Insert Value (Automated Balance)" << endl;
        cout << "2. View Adjacency List (Graph View)" << endl;
        cout << "3. View Edge-Weight Connectivity" << endl;
        cout << "0. Exit" << endl;
        cout << "Choice: ";
        
        if (!(cin >> choice)) break;

        switch (choice) {
            case 1:
                cout << "Enter integer to insert: ";
                cin >> value;
                rbt.insertValue(value);
                cout << ">> Inserted " << value << ". Tree rebalanced." << endl;
                break;

            case 2:
                cout << "\n--- Node Connections ---" << endl;
                for (size_t i = 0; i < rbt.numVertices(); ++i) {
                    vector<size_t> nbrs = rbt.neighbours(i);
                    cout << "Vertex " << i << " -> ";
                    if (nbrs.empty()) cout << "(Leaf/No Children)";
                    for (size_t n : nbrs) cout << n << " ";
                    cout << endl;
                }
                break;

            case 3:
                cout << "\n--- Edge Weights (Graph Interface) ---" << endl;
                for (size_t i = 0; i < rbt.numVertices(); ++i) {
                    for (size_t j = 0; j < rbt.numVertices(); ++j) {
                        if (rbt.hasEdge(i, j)) {
                            cout << "Edge (" << i << "," << j << ") Weight: " 
                                 << rbt.edgeWeight(i, j) << endl;
                        }
                    }
                }
                break;

            case 0:
                return 0;

            default:
                cout << "Invalid selection." << endl;
        }
    }
    return 0;
}