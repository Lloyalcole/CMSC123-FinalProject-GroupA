#include "../src/adjacencymatrix.h"
#include <iostream>
#include <string>

using namespace ods;
using namespace std;

void displayGraph(const AdjacencyMatrix& g) {
    size_t n = g.numVertices();
    cout << "\n--- Current Adjacency Matrix (" << n << "x" << n << ") ---\n";
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (g.hasEdge(i, j)) {
                cout << g.edgeWeight(i, j) << "\t";
            } else {
                cout << "-\t";
            }
        }
        cout << "\n";
    }
    cout << "Total Edges: " << g.numEdges() << "\n----------------------------\n";
}

int main() {
    size_t initial_v;
    bool is_directed;

    cout << "Enter initial number of vertices: ";
    cin >> initial_v;
    cout << "Is the graph directed? (1 for Yes, 0 for No): ";
    cin >> is_directed;

    AdjacencyMatrix g(initial_v, is_directed);

    int choice = -1;
    while (choice != 0) {
        cout << "\n1. Add Edge\n2. Remove Edge\n3. Add Vertex\n4. Remove Vertex\n5. Display Matrix\n0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        try {
            if (choice == 1) {
                size_t u, v;
                double w;
                cout << "Enter source, destination, and weight (e.g., 0 1 5.5): ";
                cin >> u >> v >> w;
                g.addEdge(u, v, w);
            } 
            else if (choice == 2) {
                size_t u, v;
                cout << "Enter source and destination to remove: ";
                cin >> u >> v;
                g.removeEdge(u, v);
            } 
            else if (choice == 3) {
                size_t new_idx = g.addVertex();
                cout << "Added vertex at index: " << new_idx << "\n";
            } 
            else if (choice == 4) {
                size_t v;
                cout << "Enter vertex index to remove (will shift others): ";
                cin >> v;
                g.removeVertex(v);
                cout << "Vertex removed.\n";
            } 
            else if (choice == 5) {
                displayGraph(g);
            }
        } catch (const out_of_range& e) {
           cerr << "Error: " << e.what() << "\n";
        }
    }

    cout << "Exiting...\n";
    return 0;
}