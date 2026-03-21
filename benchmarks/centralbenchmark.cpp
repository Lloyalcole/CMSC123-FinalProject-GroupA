#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <cstdlib> // For rand()

// Proper includes based on your directory structure
#include "../src/adjacencymatrix.h"
#include "../src/arraydeque.h"
#include "../src/arraystack.h"
#include "../src/chainedhashtable.h"
#include "../src/meldableheap.h"
#include "../src/skiplist.h"
//#include "../src/linkedlistqueue.h"
//#include "../src/redblacktree.h"

using namespace std;
using namespace std::chrono;

// Simplified Benchmark Class
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
        // Using tabs (\t) to keep columns aligned without iomanip
        cout << ds << "\t\t" << op << "\t" << n << "\t\t" << time << " ms" << endl;
    }
};

int main() {
    // Test sizes
    const int N_LG = 1000000; 
    const int N_MD = 100000;    
    const int N_SM = 5000;    

    int choice = -1;

    while (choice != 0) {
        cout << "\n--- Data Structure Benchmark Tool ---" << endl;
        cout << "1. Array Stack (FILO)" << endl;
        cout << "2. Linked List Queue (FIFO)" << endl;
        cout << "3. Array Deque" << endl;
        cout << "4. Red-Black Tree" << endl;
        cout << "5. SkipList" << endl;
        cout << "6. Chained Hash Table" << endl;
        cout << "7. Meldable Heap" << endl;
        cout << "8. Adjacency Matrix" << endl;
        cout << "9. Run All Benchmarks" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 0) break;

        // Header is only printed if a valid test is chosen
        if (choice >= 1 && choice <= 9) BasicBenchmark::printHeader();

        // Lambda functions for each test to avoid repeating code in Case 9
        auto runStack = [&]() {
            ArrayStack<int> s;
            double t = BasicBenchmark::measure([&]() {
                for(int i = 0; i < N_LG; ++i) s.push(rand());
                for(int i = 0; i < N_LG; ++i) s.pop();
            });
            BasicBenchmark::printLine("ArrayStack", "Push/Pop", N_LG, t);
        };

        auto runQueue = [&]() {
            LinkedListQueue<int> q;
            double t = BasicBenchmark::measure([&]() {
                for(int i = 0; i < N_LG; ++i) q.enqueue(rand());
                for(int i = 0; i < N_LG; ++i) q.dequeue();
            });
            BasicBenchmark::printLine("L-ListQueue", "Enq/Deq", N_LG, t);
        };

        auto runDeque = [&]() {
            ArrayDeque<int> d;
            double t = BasicBenchmark::measure([&]() {
                for(int i = 0; i < N_LG; ++i) d.addBack(rand());
                for(int i = 0; i < N_LG; ++i) d.removeFront();
            });
            BasicBenchmark::printLine("ArrayDeque", "Add/Rem", N_LG, t);
        };

        auto runRBT = [&]() {
            RedBlackTree<int> rbt;
            double t = BasicBenchmark::measure([&]() {
                for(int i = 0; i < N_MD; ++i) rbt.add(rand());
            });
            BasicBenchmark::printLine("RedBlackTree", "Insert", N_MD, t);
        };

        auto runSkip = [&]() {
            SkipList<int> sk;
            double t = BasicBenchmark::measure([&]() {
                for(int i = 0; i < N_MD; ++i) sk.add(rand());
            });
            BasicBenchmark::printLine("SkipList", "Insert", N_MD, t);
        };

        auto runHash = [&]() {
            ChainedHashTable<int> h;
            double t = BasicBenchmark::measure([&]() {
                for(int i = 0; i < N_LG; ++i) h.add(rand());
            });
            BasicBenchmark::printLine("HashTable", "Insert", N_LG, t);
        };

        auto runHeap = [&]() {
            MeldableHeap<int> mh;
            double t = BasicBenchmark::measure([&]() {
                for(int i = 0; i < N_MD; ++i) mh.add(rand());
                for(int i = 0; i < N_MD; ++i) mh.remove();
            });
            BasicBenchmark::printLine("MeldableHeap", "Add/Rem", N_MD, t);
        };

        auto runGraph = [&]() {
            AdjacencyMatrix g(N_SM);
            double t = BasicBenchmark::measure([&]() {
                for(int i = 0; i < N_SM - 1; ++i) g.addEdge(i, i+1);
            });
            BasicBenchmark::printLine("AdjMatrix", "AddEdge", N_SM, t);
        };

        switch (choice) {
            case 1: runStack(); break;
            case 2: runQueue(); break;
            case 3: runDeque(); break;
            case 4: runRBT();   break;
            case 5: runSkip();  break;
            case 6: runHash();  break;
            case 7: runHeap();  break;
            case 8: runGraph(); break;
            case 9:
                runStack(); runQueue(); runDeque();
                runRBT(); runSkip(); runHash();
                runHeap(); runGraph();
                break;
            default: cout << "Invalid choice." << endl;
        }
    }

    return 0;
}