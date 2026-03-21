#include <iostream>
#include <stdexcept>
#include "../src/meldableheap.h"

using namespace std;

int main() {
    MeldableHeap<int> heap;

    cout << "CMSC 123 MeldableHeap Test: Sir Eli Checks the Repo\n\n";

    cout << "Sir Eli opens the gradebook. Time to record the scores.\n";
    cout << "Hannah submitted first. Her score: 92\n";
    heap.add(92);
    cout << "Nino submitted next. His score: 78\n";
    heap.add(78);
    cout << "Cole submitted. His score: 85\n";
    heap.add(85);
    cout << "Drebin submitted last. His score: 60\n";
    heap.add(60);
    cout << "Total scores recorded: " << heap.size() << "\n";

    cout << "\n Sir Eli wants to know the lowest score without removing it.\n";
    cout << "Lowest score so far: " << heap.peek() << " (Should be 60)\n";

    cout << "\n Late submissions arrive...\n";
    cout << "A wild score of 45 appears. Someone really gave up.\n";
    heap.add(45);
    cout << "Another score: 99. Someone was too good for this class.\n";
    heap.add(99);
    cout << "Total scores recorded: " << heap.size() << "\n";

    cout << "\n Sir Eli peeks again at the lowest score.\n";
    cout << "Lowest score: " << heap.peek() << " (Should be 45)\n";

    // --- remove ---
    cout << "\n Sir Eli starts processing scores from lowest to highest.\n";
    cout << "Processing score: " << heap.remove() << " (Should be 45)\n";
    cout << "Processing score: " << heap.remove() << " (Should be 60)\n";
    cout << "Processing score: " << heap.remove() << " (Should be 78)\n";
    cout << "Remaining scores: " << heap.size() << "\n";

    cout << "\n A second group's heap arrives. Sir Eli merges them together.\n";
    MeldableHeap<int> heap2;
    heap2.add(55);
    heap2.add(70);
    heap2.add(88);
    cout << "Second heap has " << heap2.size() << " scores: 55, 70, 88\n";
    heap.absorb(heap2);
    cout << "After absorb — main heap size: " << heap.size() << "\n";
    cout << "Second heap empty? " << (heap2.isEmpty() ? "Yes, absorbed." : "No, still has elements.") << "\n";

    cout << "\n Sir Eli processes all remaining scores in order:\n   ";
    while (!heap.isEmpty())
    {
        cout << heap.remove() << " ";
    }
    cout << "\n";

    // --- isEmpty ---
    cout << "\nHeap empty? " << (heap.isEmpty() ? "Yes. Heap is empty." : "No, heap is not empty.") << "\n";

    cout << "\n Testing for exceptions...\n";
    cout << "Sir Eli tries to remove from an empty heap...\n";
    try {
        heap.remove();
    } catch (const out_of_range& e) {
        cout << "Error caught: " << e.what() << "\n";
    }

    cout << "Sir Eli tries to peek at an empty heap...\n";
    try {
        heap.peek();
    } catch (const out_of_range& e) {
        cout << "Error caught: " << e.what() << "\n";
    }

    cout << "\n Sir Eli closes the gradebook. Grade: TBD.\n";

    return 0;
}