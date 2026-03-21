#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <cstdlib> 

// Headers provided in your snippet
#include "../src/adjacencymatrix.h"
#include "../src/arraydeque.h"
#include "../src/arraystack.h"
#include "../src/chainedhashtable.h"
#include "../src/meldableheap.h"
#include "../src/skiplist.h"

// Note: Ensure these exist in your include path if you uncomment them
// #include "../src/linkedlistqueue.h" 
// #include "../src/redblacktree.h"

using namespace std;
using namespace std::chrono;

class BasicBenchmark {
public:
    static void printHeader() {
        cout << "\nData Structure\t\tOperation\tCount\t\tTime (ms)" << endl;
        cout << "------------------------------------------------------------------------" << endl;
    }

    template <typename Func>
    static double measure(Func f) {
        auto start = high_resolution_clock::now();
        f();
        auto end = high_resolution_clock::now();
        duration<double, milli> elapsed = end - start;
        return elapsed.count();
    }

    static void printLine(string ds, string op, int n, double time) {
        cout << ds << "\t\t" << op << "\t" << n << "\t\t" << time << " ms" << endl;
    }
};

int main() {
    const int N_LG = 100000; 
    const int N_MD = 10000;    
    const int N_SM = 1000;    

    int choice = -1;

    while (true) {
        cout << "\n--- Data Structure Benchmark Tool ---" << endl;
        cout << "1. Array Stack" << endl;
        cout << "2. Array Deque" << endl;
        cout << "3. SkipList" << endl;
        cout << "4. Chained Hash Table" << endl;
        cout << "5. Meldable Heap" << endl;
        cout << "6. Adjacency Matrix" << endl;
        cout << "9. Run All Available" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 0) break;
        BasicBenchmark::printHeader();

        auto runArrayStack = [&]() {
            ods::ArrayStack<int> s;
            double t = BasicBenchmark::measure([&]() {
                for(int i = 0; i < N_LG; ++i) s.push(rand());
                for(int i = 0; i < N_LG; ++i) s.pop();
            });
            BasicBenchmark::printLine("ArrayStack", "Push/Pop", N_LG, t);
        };

        auto runArrayDeque = [&]() {
            ArrayDeque<int> d;
            double t = BasicBenchmark::measure([&]() {
                for(int i = 0; i < N_LG; ++i) d.addLast(rand()); 
                for(int i = 0; i < N_LG; ++i) d.removeFirst(); 
            });
            BasicBenchmark::printLine("ArrayDeque", "AddL/RemF", N_LG, t);
        };

        auto runSkipList = [&]() {
            ods::SkipList<int> sk;
            double t = BasicBenchmark::measure([&]() {
                for(int i = 0; i < N_MD; ++i) sk.add(rand());
            });
            BasicBenchmark::printLine("SkipList", "Insert", N_MD, t);
        };

        auto runHashTable = [&]() {
            ods::ChainedHashTable<int> h(N_LG); 
            double t = BasicBenchmark::measure([&]() {
                for(int i = 0; i < N_LG; ++i) h.add(rand());
            });
            BasicBenchmark::printLine("HashTable", "Insert", N_LG, t);
        };

        auto runMeldableHeap = [&]() {
            MeldableHeap<int> mh;
            double t = BasicBenchmark::measure([&]() {
                for(int i = 0; i < N_MD; ++i) mh.add(rand());
                for(int i = 0; i < N_MD; ++i) mh.remove();
            });
            BasicBenchmark::printLine("MeldableHeap", "Add/Rem", N_MD, t);
        };

        auto runAdjacencyMatrix = [&]() {
            ods::AdjacencyMatrix g(N_SM);
            double t = BasicBenchmark::measure([&]() {
                for(int i = 0; i < N_SM - 1; ++i) g.addEdge(i, i+1);
            });
            BasicBenchmark::printLine("AdjacencyMatrix", "AddEdge", N_SM, t);
        };

        switch (choice) {
            case 1: runArrayStack(); break;
            case 2: runArrayDeque(); break;
            case 3: runSkipList();  break;
            case 4: runHashTable();  break;
            case 5: runMeldableHeap();  break;
            case 6: runAdjacencyMatrix(); break;
            case 9:
                runArrayStack(); runArrayDeque(); runSkipList(); 
                runHashTable(); runMeldableHeap(); runAdjacencyMatrix();
                break;
            default: cout << "Invalid choice or implementation missing." << endl;
        }
    }
    return 0;
}