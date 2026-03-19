#include <iostream>
#include <string>
#include "../src/arraystack.h"

using namespace std;
using namespace ods;

void printMenu() {
    cout << "\n--- Stack Test Menu ---" << endl;
    cout << "1. Push" << endl;
    cout << "2. Pop" << endl;
    cout << "3. Peek" << endl;
    cout << "4. Size" << endl;
    cout << "5. Is Empty?" << endl;
    cout << "6. Clear" << endl;
    cout << "7. Quit" << endl;
    cout << "Choice: ";
}

int main() {
    ArrayStack<int> s;
    int choice, val;
    bool running = true;

    while (running) {
        printMenu();
        if (!(cin >> choice)) break; // Safety check for non-numeric input

        switch (choice) {
            case 1:
                cout << "Enter value to push: ";
                cin >> val;
                s.push(val);
                cout << "Pushed " << val << endl;
                break;

            case 2:
                // Is it safe to pop?
                if (!s.empty()) {
                    cout << "Popped: " << s.pop() << endl;
                } else {
                    cout << "Error: Cannot pop. The stack is empty!" << endl;
                }
                break;

            case 3:
                // Is it safe to peek?
                if (!s.empty()) {
                    cout << "Top: " << s.peek() << endl;
                } else {
                    cout << "Error: The stack is empty!" << endl;
                }
                break;

            case 4:
                cout << "Size: " << s.size() << endl;
                break;

            case 5:
                cout << (s.empty() ? "Stack is empty" : "Stack is NOT empty") << endl;
                break;

            case 6:
                s.clear();
                cout << "Stack cleared." << endl;
                break;

            case 7:
                running = false;
                break;

            default:
                cout << "Invalid choice!" << endl;
        }
    }
    return 0;
}