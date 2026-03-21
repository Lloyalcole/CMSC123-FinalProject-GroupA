#include <iostream>
#include <stdexcept>
#include <string>
#include "../src/arraydeque.h"

using namespace std;
using namespace ods; 

template <typename T>
void printRow(ArrayDeque<T>& dq) {
    cout << "[Row: ";
    for (size_t i = 0; i < dq.size(); ++i) {
        if (i > 0) cout << " <-> ";
        cout << dq.get(i);
    }
    cout << "]\n";
}

int main() {
    ArrayDeque<string> dq;

    cout << "CMSC 123 ArrayDeque Test: Sir Eli Checks the Repo\n\n";

    cout << "Sir Eli opens the GitHub repo link. He scrolls to the test file.\n";
    cout << "The group has 4 members. First to commit was Hannah.\n";
    dq.addFirst("Hannah");
    printRow(dq);

    cout << "\nCole pushed his changes right after Hannah.\n";
    dq.addLast("Cole");
    printRow(dq);

    cout << "\nNino realized he forgot to add his name to the contributors.\n";
    cout << "   He squeezed in between Hannah and Cole (index 1).\n";
    dq.add(1, "Nino");
    printRow(dq);

    cout << "\nDrebin was the last to push. He added himself at the very back.\n";
    dq.addLast("Drebin");
    printRow(dq);

    cout << "\n Sir Eli starts reading the commits...\n";
    cout << "Sir Eli asks: 'Who committed first?'\n";
    cout << "Result: " << dq.peekFirst() << " (Should be Hannah)\n";

    cout << "Sir Eli asks: 'Who committed last?'\n";
    cout << "Result: " << dq.peekLast() << " (Should be Drebin)\n";

    cout << "Sir Eli asks: 'Who is at index 2?'\n";
    cout << "Result: " << dq.get(2) << " (Should be Cole, sweating nervously)\n";

    cout << "\n WAIT. Sir Eli notices a 5th contributor???\n";
    cout << "Turns out Hannah made a second account named HannahAlt.\n";
    cout << "She inserted herself at the very front again (index 0).\n";
    dq.addFirst("HannahAlt");
    printRow(dq);

    cout << "\nSir Eli: 'HannahAlt is not a valid name.'\n";
    cout << "Hannah panics and changes it to her real name at index 0.\n";
    dq.set(0, "Hannah Reyes");
    printRow(dq);

    cout << "\n Sir Eli checks the repo one last time before grading.\n";
    cout << "Hannah Reyes is removed from index 0 for having two accounts.\n";
    cout << "Removed: " << dq.removeFirst() << "\n";
    printRow(dq);

    cout << "\nCole's code had a memory leak. Sir Eli removes him at index 2.\n";
    cout << "Removed: " << dq.remove(2) << "\n";
    printRow(dq);

    cout << "\nDrebin pushed an empty commit. Removed from the back.\n";
    cout << "Removed: " << dq.removeLast() << "\n";
    printRow(dq);

    cout << "\nHow many members are left? " << dq.size() << "\n";
    cout << "Is the repo empty? " << (dq.isEmpty() ? "Yes, everyone got removed." : "No, someone survived.") << "\n";

    cout << "\n Sir Eli clears the contributor list and starts a new rubric.\n";
    dq.clear();
    cout << "Is it empty now? " << (dq.isEmpty() ? "Yes. Wala nang natira." : "Still has members.") << "\n";

    cout << "\n Testing for exceptions...\n";
    cout << "Sir Eli tries to check who is at index 100...\n";
    try {
        dq.get(100);
    } catch (const out_of_range& e) {
        cout << "Error caught: " << e.what() << "\n";
    }

    cout << "Sir Eli tries to remove from an empty deque...\n";
    try {
        dq.removeFirst();
    } catch (const out_of_range& e) {
        cout << "Error caught: " << e.what() << "\n";
    }

    cout << "\n Sir Eli closes the laptop. Grade: TBD.\n";

    return 0;
}