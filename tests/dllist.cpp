#include <iostream>
#include <string>
#include "../src/dllist.h"

using namespace std;
using namespace ods;

void printMenu() {
    cout << "\n--- Welcome to Group A's Doubly Linked List ---" << endl;
    cout << "1. Add at index" << endl;
    cout << "2. Basic Add" << endl;
    cout << "3. Remove at index" << endl;
    cout << "4. Get value at index" << endl;
    cout << "5. Set value at index" << endl;
    cout << "6. Size" << endl;
    cout << "7. Print list" << endl;
    cout << "8. Quit" << endl;
    cout << "Choice: ";
}

template <typename T>
void printList(DLList<T>& list) {
    cout << "[";
    for (size_t i = 0; i < list.size(); ++i) {
        if (i > 0) cout << " <-> ";
        cout << list.get(i);
    }
    cout << "]" << endl;
}

int main() {
    ods::DLList<string> list;
    int choice;
    size_t index;
    string value;
    bool running = true;

    while (running) {
        printMenu();
        if (!(cin >> choice)) break;

        switch (choice) {
            case 1: 
                cout << "Enter index: ";
                cin >> index;
                cout << "Enter value: ";
                cin.ignore();
                getline(cin, value);
                try {
                    list.add(index, value);
                    cout << "Added \"" << value << "\" at index " << index << endl;
                } catch (const out_of_range&) {
                    cout << "Error: Index out of range." << endl;
                }
                break;
            case 2:
                cout << "Enter value: ";
                cin.ignore();
                getline(cin, value);
                list.add(list.size(), value);
                break;
            case 3:
                cout << "Enter index to remove: ";
                cin >> index;
                try {
                    cout << "Removed: " << list.remove(index) << endl;
                } catch (const out_of_range&) {
                    cout << "Error: Index out of range." << endl;
                }
                break;
            case 4:
                cout << "Enter index to get: ";
                cin >> index;
                try {
                    cout << "Value: " << list.get(index) << endl;
                } catch (const out_of_range&) {
                    cout << "Error: Out of range." << endl;
                }
                break;
            case 5:
                cout << "Enter index to set: ";
                cin >> index;
                cout << "Enter new value: ";
                cin.ignore();
                getline(cin, value);
                try {
                    cout << "Old value: " << list.set(index, value) << endl;
                } catch (const out_of_range&) {
                    cout << "Error: Out of range." << endl;
                }
                break;
            case 6:
                cout << "Size: " << list.size() << endl;
                break;
            case 7:
                printList(list);
                break;
            case 8:
                running = false;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    }
    return 0;
}