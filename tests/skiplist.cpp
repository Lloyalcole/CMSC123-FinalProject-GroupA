#include <iostream>
#include <string>
#include "../include/sset.h"  
#include "../src/skiplist.h"

using namespace std;
using namespace ods;

void printSLMenu() {
    cout << "\n--- SkipList (Sorted Set) Test ---" << endl;
    cout << "1. Add Element" << endl;
    cout << "2. Remove Element" << endl;
    cout << "3. Contains?" << endl;
    cout << "4. Quit" << endl;
    cout << "Choice: ";
}

int main() {
    SkipList<int> sl;
    int choice, val;

    while (true) {
        printSLMenu();
        if (!(cin >> choice)) break;

        if (choice == 4) break;

        cout << "Enter integer value: ";
        cin >> val;

        switch (choice) {
            case 1:
                sl.add(val);
                cout << "Inserted " << val << " into the SkipList." << endl;
                break;
            case 2:
                sl.remove(val);
                cout << "Removed " << val << " (if it existed)." << endl;
                break;
            case 3:
                if (sl.contains(val)) cout << val << " is present in the list!" << endl;
                else cout << val << " is NOT present." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    }
    return 0;
}