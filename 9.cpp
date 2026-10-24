#include <iostream>
using namespace std;

class CircularLinkedList {
private:
    // Encapsulated node structure
    struct Node {
        int data;
        Node *next;

        Node(int value) {
            data = value;
            next = nullptr;
        }
    };

    Node *tail;

public:
    CircularLinkedList() {
        tail = nullptr;
    }

    // Destructor: Safely breaks circular link before deleting nodes
    ~CircularLinkedList() {
        if (tail == nullptr)
            return;

        Node *head = tail->next;
        tail->next = nullptr; // Convert to linear list for cleanup

        while (head != nullptr) {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }

    void insert(int value) {
        Node *newNode = new Node(value);

        if (tail == nullptr) {
            tail = newNode;
            tail->next = tail;
            return;
        }

        newNode->next = tail->next;
        tail->next = newNode;
        tail = newNode;
    }

    void deleteElement(int value) {
        if (tail == nullptr) {
            cout << "List is empty\n";
            return;
        }

        Node *current = tail->next;
        Node *previous = tail;

        do {
            if (current->data == value) {
                // Case 1: Single element list
                if (current == tail && current->next == tail) {
                    delete current;
                    tail = nullptr;
                } 
                // Case 2: Multi-element list
                else {
                    previous->next = current->next;
                    if (current == tail)
                        tail = previous;
                    delete current;
                }
                cout << value << " deleted successfully\n";
                return;
            }

            previous = current;
            current = current->next;
        } while (current != tail->next);

        cout << "Element not found\n";
    }

    bool search(int value) {
        if (tail == nullptr)
            return false;

        Node *current = tail->next;

        do {
            if (current->data == value)
                return true;
            current = current->next;
        } while (current != tail->next);

        return false;
    }

    void display() {
        if (tail == nullptr) {
            cout << "List is empty\n";
            return;
        }

        Node *current = tail->next;

        cout << "Circular List: ";
        do {
            cout << current->data << " -> ";
            current = current->next;
        } while (current != tail->next);

        cout << "(back to start: " << tail->next->data << ")\n";
    }

    int countNodes() {
        if (tail == nullptr)
            return 0;

        int count = 0;
        Node *current = tail->next;

        do {
            count++;
            current = current->next;
        } while (current != tail->next);

        return count;
    }

    // Static helper method to solve Josephus Problem independently
    static int solveJosephus(int n, int k) {
        if (n <= 0 || k <= 0) return -1;

        CircularLinkedList circle;
        for (int i = 1; i <= n; i++)
            circle.insert(i);

        Node *current = circle.tail->next;
        Node *previous = circle.tail;

        cout << "\n--- Josephus Elimination Process (n=" << n << ", k=" << k << ") ---\n";

        while (current->next != current) {
            // Traverse k-1 steps
            for (int step = 1; step < k; step++) {
                previous = current;
                current = current->next;
            }

            // Eliminate k-th node
            cout << "Eliminated person: " << current->data << "\n";
            previous->next = current->next;

            if (current == circle.tail)
                circle.tail = previous;

            Node *temp = current;
            current = current->next;
            delete temp;
        }

        int survivor = current->data;
        // Detach survivor to prevent double deletion during destructor run
        circle.tail = current;
        circle.tail->next = circle.tail;

        return survivor;
    }
};

int main() {
    CircularLinkedList list;
    int choice, value, n, k;

    do {
        cout << "\n--- Circular Linked List Menu ---\n"
             << "1. Insert Element\n"
             << "2. Delete Element\n"
             << "3. Search Element\n"
             << "4. Display List\n"
             << "5. Count Nodes\n"
             << "6. Solve Josephus Problem\n"
             << "7. Exit\n"
             << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                list.insert(value);
                break;

            case 2:
                cout << "Enter value to delete: ";
                cin >> value;
                list.deleteElement(value);
                break;

            case 3:
                cout << "Enter value to search: ";
                cin >> value;
                cout << (list.search(value) ? "Element found in list\n" : "Element not found\n");
                break;

            case 4:
                list.display();
                break;

            case 5:
                cout << "Total nodes: " << list.countNodes() << endl;
                break;

            case 6:
                cout << "Enter number of people (n): ";
                cin >> n;
                cout << "Enter step size (k): ";
                cin >> k;
                cout << "Survivor position: " << CircularLinkedList::solveJosephus(n, k) << endl;
                break;

            case 7:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice\n";
        }
    } while (choice != 7);

    return 0;
}