#include <iostream>
#include <string>
#include "../src/sllistqueue.h"

using namespace std;

void printMenu() {
    cout << "\n--- Welcome to Group A's Singly Linked List Queue ---" << endl;
    cout << "1. Enqueue" << endl;
    cout << "2. Dequeue" << endl;
    cout << "3. Front" << endl;
    cout << "4. Size" << endl;
    cout << "5. Is Empty?" << endl;
    cout << "6. Clear" << endl;
    cout << "7. Print queue" << endl;
    cout << "8. Quit" << endl;
    cout << "Choice: ";
}

template <typename T>
void printQueue(SLListQueue<T>& q) {
    SLListQueue<T> temp;

    cout << "[Front: ";
    bool first = true;

    while (!q.isEmpty()) {
        T x = q.dequeue();
        if (!first) cout << " -> ";
        cout << x;
        temp.enqueue(x);
        first = false;
    }

    cout << " :Back]" << endl;

    while (!temp.isEmpty()) {
        q.enqueue(temp.dequeue());
    }
}

int main() {
    SLListQueue<string> q;
    int choice;
    string value;
    bool running = true;

    while (running) {
        printMenu();
        if (!(cin >> choice)) break;

        switch (choice) {
            case 1:
                cout << "You chose to enqueue!" << endl;
                cout << "Please enter value to enqueue: ";
                cin.ignore();
                getline(cin, value);
                q.enqueue(value);
                cout << "Enqueued: " << value << endl;
                break;

            case 2:
                cout << "You chose to dequeue!" << endl;
                if (!q.isEmpty()) {
                    cout << "Dequeued: " << q.dequeue() << endl;
                } else {
                    cout << "Error: Cannot dequeue. The queue is empty!" << endl;
                }
                break;

            case 3:
                cout << "You chose to get the front!" << endl;
                if (!q.isEmpty()) {
                    cout << "Front: " << q.front() << endl;
                } else {
                    cout << "Error: The queue is empty!" << endl;
                }
                break;

            case 4:
                cout << "You chose to get the size!" << endl;
                cout << "Size: " << q.size() << endl;
                break;

            case 5:
                cout << "You chose to see if the queue is empty!" << endl;
                cout << (q.isEmpty() ? "Queue is empty" : "Queue is NOT empty") << endl;
                break;

            case 6:
                char confirm;
                cout << "Did you really choose to clear the queue? (Y/N): ";
                cin >> confirm;
                while (confirm != 'Y' && confirm != 'y' &&
                    confirm != 'N' && confirm != 'n') {
                    cout << "Invalid input. Please enter Y or N: ";
                    cin >> confirm;
                }
                if (confirm == 'Y' || confirm == 'y') {
                    q.clear();
                    cout << "Queue cleared." << endl;
                } else {
                    cout << "Yeah, I thought so too." << endl;
                }
                break;           

            case 7:
                cout << "Current queue: ";
                printQueue(q);
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