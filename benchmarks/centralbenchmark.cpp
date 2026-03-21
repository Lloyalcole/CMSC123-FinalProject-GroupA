#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <cstdlib> 
#include <iomanip> 

#include "../src/adjacencymatrix.h"
#include "../src/arraydeque.h"
#include "../src/arraystack.h"
#include "../src/chainedhashtable.h"
#include "../src/dllist.h"
#include "../src/meldableheap.h"
#include "../src/redblacktrees.h"
#include "../src/skiplist.h"
#include "../src/sllistqueue.h" 

using namespace std;
using namespace std::chrono;

class BasicBenchmark {
public:
    static void printHeader() {
        cout << "\n" << left << setw(20) << "Data Structure" 
             << setw(20) << "Operation" 
             << setw(15) << "Count" 
             << "Time (ms)" << endl;
        cout << string(65, '-') << endl;
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
        cout << left << setw(20) << ds 
             << setw(20) << op 
             << setw(15) << n 
             << fixed << setprecision(4) << time << " ms" << endl;
    }
};

int main() {
    const int LargeNum = 100000; 
    const int MediumNum = 10000;  
    const int SmallNum = 1000;   

    int choice = -1;

    while (true) {
        cout << "\n--- CMSC123 Central Benchmark Tool ---" << endl;
        cout << "1. Array Stack" << endl;
        cout << "2. Array Deque" << endl;
        cout << "3. SkipList" << endl;
        cout << "4. Chained Hash Table" << endl;
        cout << "5. Meldable Heap" << endl;
        cout << "6. Adjacency Matrix" << endl;
        cout << "7. SLL Queue" << endl;
        cout << "8. Red-Black Tree" << endl;
        cout << "9. Doubly Linked List (DLList)" << endl;
        cout << "10. Run All Available" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 0) break;
        BasicBenchmark::printHeader();

        // 1. Array Stack
        auto runArrayStack = [&]() {
            ods::ArrayStack<int> s;
            double t = BasicBenchmark::measure([&]() {
                for(int i = 0; i < LargeNum; ++i) s.push(rand());
                for(int i = 0; i < LargeNum; ++i) s.pop();
            });
            BasicBenchmark::printLine("ArrayStack", "Push/Pop", LargeNum, t);
        };

        // 2. Array Deque
        auto runArrayDeque = [&]() {
            ods::ArrayDeque<int> d;
            double t = BasicBenchmark::measure([&]() {
                for(int i = 0; i < LargeNum; ++i) d.addLast(rand()); 
                for(int i = 0; i < LargeNum; ++i) d.removeFirst(); 
            });
            BasicBenchmark::printLine("ArrayDeque", "AddL/RemF", LargeNum, t);
        };

        // 3. SkipList
        auto runSkipList = [&]() {
            ods::SkipList<int> sk;
            double t = BasicBenchmark::measure([&]() {
                for(int i = 0; i < MediumNum; ++i) sk.add(rand());
            });
            BasicBenchmark::printLine("SkipList", "Insert", MediumNum, t);
        };

        // 4. Chained Hash Table
        auto runHashTable = [&]() {
            ods::ChainedHashTable<int> h; 
            double t = BasicBenchmark::measure([&]() {
                for(int i = 0; i < LargeNum; ++i) h.add(rand());
            });
            BasicBenchmark::printLine("HashTable", "Insert", LargeNum, t);
        };

        // 5. Meldable Heap
        auto runMeldableHeap = [&]() {
            ods::MeldableHeap<int> mh;
            double t = BasicBenchmark::measure([&]() {
                for(int i = 0; i < MediumNum; ++i) mh.add(rand());
                for(int i = 0; i < MediumNum; ++i) mh.remove();
            });
            BasicBenchmark::printLine("MeldableHeap", "Add/Rem", MediumNum, t);
        };

        // 6. Adjacency Matrix
        auto runAdjacencyMatrix = [&]() {
            ods::AdjacencyMatrix g(SmallNum);
            double t = BasicBenchmark::measure([&]() {
                for(int i = 0; i < SmallNum - 1; ++i) g.addEdge(i, i+1);
            });
            BasicBenchmark::printLine("AdjMatrix", "AddEdge", SmallNum, t);
        };

        // 7. SLList Queue
        auto runSLLQueue = [&]() {
            ods::SLListQueue<int> q;
            double t = BasicBenchmark::measure([&]() {
                for(int i = 0; i < LargeNum; ++i) q.enqueue(rand());
                for(int i = 0; i < LargeNum; ++i) q.dequeue();
            });
            BasicBenchmark::printLine("SLLQueue", "Enq/Deq", LargeNum, t);
        };

        // 8. Red-Black Tree
        auto runRBT = [&]() {
            ods::RedBlackTree rbt;
            double t = BasicBenchmark::measure([&]() {
                for(int i = 0; i < MediumNum; ++i) rbt.insertValue(rand());
            });
            BasicBenchmark::printLine("RedBlackTree", "BalancedIns", MediumNum, t);
        };

        // 9. Doubly Linked List
        auto runDLList = [&]() {
            ods::DLList<int> dll;
            double t = BasicBenchmark::measure([&]() {
                for(int i = 0; i < MediumNum; ++i) dll.add(0, rand());
                for(int i = 0; i < MediumNum; ++i) dll.remove(0);
            });
            BasicBenchmark::printLine("DLList", "HeadAdd/Rem", MediumNum, t);
        };

        switch (choice) {
            case 1: runArrayStack(); break;
            case 2: runArrayDeque(); break;
            case 3: runSkipList();   break;
            case 4: runHashTable();  break;
            case 5: runMeldableHeap(); break;
            case 6: runAdjacencyMatrix(); break;
            case 7: runSLLQueue(); break;
            case 8: runRBT(); break;
            case 9: runDLList(); break;
            case 10:
                runArrayStack(); runArrayDeque(); runSkipList(); 
                runHashTable(); runMeldableHeap(); runAdjacencyMatrix();
                runSLLQueue(); runRBT(); runDLList();
                break;
            default: cout << "Invalid choice." << endl;
        }
    }
    return 0;
}