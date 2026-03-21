#include <iostream>
#include <string>
#include "../src/chainedhashtable.h"

using namespace std;
using namespace ods;

void printHTMenu() {
    cout << "\n--- Hash Table (Unsorted Set) Test ---" << endl;
    cout << "1. Add Element" << endl;
    cout << "2. Remove Element" << endl;
    cout << "3. Contains?" << endl;
    cout << "4. Quit" << endl;
    cout << "Choice: ";
}

int main() {
    ChainedHashTable<int> ht(101); // Capacity of 101
    int choice, val;

    while (true) {
        printHTMenu();
        if (!(cin >> choice)) break;

        if (choice == 4) break;

        cout << "Enter integer value: ";
        cin >> val;

        switch (choice) {
            case 1:
                ht.add(val);
                cout << "Added " << val << " to the table." << endl;
                break;
            case 2:
                ht.remove(val);
                cout << "Attempted to remove " << val << "." << endl;
                break;
            case 3:
                if (ht.contains(val)) cout << val << " is in the set!" << endl;
                else cout << val << " was NOT found." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    }
    return 0;
}