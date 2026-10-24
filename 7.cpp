#include <iostream>
using namespace std;

class SinglyLinkedList {
private:
    // Nesting Node inside private maintains strict OOP encapsulation
    struct Node {
        int data;
        Node *next;

        Node(int val) {
            data = val;
            next = nullptr;
        }
    };

    Node *head;

public:
    SinglyLinkedList() {
        head = nullptr;
    }

    // Destructor: Frees dynamically allocated memory
    ~SinglyLinkedList() {
        Node *cur = head;
        while (cur != nullptr) {
            Node *next = cur->next;
            delete cur;
            cur = next;
        }
    }

    void insertAtBeginning(int val) {
        Node *newNode = new Node(val);
        newNode->next = head;
        head = newNode;
    }

    void insertAtEnd(int val) {
        Node *newNode = new Node(val);
        if (!head) {
            head = newNode;
            return;
        }
        Node *cur = head;
        while (cur->next) {
            cur = cur->next;
        }
        cur->next = newNode;
    }

    // 1-indexed position
    void insertAtPosition(int val, int pos) {
        if (pos <= 1) {
            insertAtBeginning(val);
            return;
        }
        Node *cur = head;
        for (int i = 1; i < pos - 1 && cur; i++) {
            cur = cur->next;
        }
        if (!cur) {
            cout << "Position out of range\n";
            return;
        }
        Node *newNode = new Node(val);
        newNode->next = cur->next;
        cur->next = newNode;
    }

    void deleteFromBeginning() {
        if (!head) {
            cout << "List is empty\n";
            return;
        }
        Node *temp = head;
        head = head->next;
        delete temp;
    }

    void deleteFromEnd() {
        if (!head) {
            cout << "List is empty\n";
            return;
        }
        if (!head->next) {
            delete head;
            head = nullptr;
            return;
        }
        Node *cur = head;
        while (cur->next->next) {
            cur = cur->next;
        }
        delete cur->next;
        cur->next = nullptr;
    }

    void deleteValue(int val) {
        if (!head) {
            cout << "List is empty\n";
            return;
        }
        if (head->data == val) {
            deleteFromBeginning();
            return;
        }
        Node *cur = head;
        while (cur->next && cur->next->data != val) {
            cur = cur->next;
        }
        if (!cur->next) {
            cout << "Value not found\n";
            return;
        }
        Node *temp = cur->next;
        cur->next = temp->next;
        delete temp;
    }

    bool search(int val) {
        Node *cur = head;
        while (cur) {
            if (cur->data == val) return true;
            cur = cur->next;
        }
        return false;
    }

    void reverse() {
        Node *prev = nullptr;
        Node *cur = head;
        Node *next = nullptr;

        while (cur) {
            next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        head = prev;
    }

    void display() {
        if (!head) {
            cout << "List is empty\n";
            return;
        }
        Node *cur = head;
        while (cur) {
            cout << cur->data << " -> ";
            cur = cur->next;
        }
        cout << "NULL\n";
    }

    int countNodes() {
        int count = 0;
        Node *cur = head;
        while (cur) {
            count++;
            cur = cur->next;
        }
        return count;
    }
};

int main() {
    SinglyLinkedList list;
    int choice, val, pos;

    do {
        cout << "\n--- Singly Linked List Menu ---\n"
             << "1. Insert At Beginning\n"
             << "2. Insert At End\n"
             << "3. Insert At Position\n"
             << "4. Delete From Beginning\n"
             << "5. Delete From End\n"
             << "6. Delete Value\n"
             << "7. Search Element\n"
             << "8. Reverse List\n"
             << "9. Display List\n"
             << "10. Count Nodes\n"
             << "11. Exit\n"
             << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value: ";
                cin >> val;
                list.insertAtBeginning(val);
                break;
            case 2:
                cout << "Enter value: ";
                cin >> val;
                list.insertAtEnd(val);
                break;
            case 3:
                cout << "Enter value: ";
                cin >> val;
                cout << "Enter position: ";
                cin >> pos;
                list.insertAtPosition(val, pos);
                break;
            case 4:
                list.deleteFromBeginning();
                break;
            case 5:
                list.deleteFromEnd();
                break;
            case 6:
                cout << "Enter value to delete: ";
                cin >> val;
                list.deleteValue(val);
                break;
            case 7:
                cout << "Enter value to search: ";
                cin >> val;
                cout << (list.search(val) ? "Element found in list\n" : "Element not found\n");
                break;
            case 8:
                list.reverse();
                cout << "List reversed successfully\n";
                break;
            case 9:
                list.display();
                break;
            case 10:
                cout << "Total nodes: " << list.countNodes() << endl;
                break;
            case 11:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice\n";
        }
    } while (choice != 11);

    return 0;
}