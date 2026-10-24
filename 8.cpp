#include <iostream>
using namespace std;

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node *prev;
        Node *next;

        Node(int val) {
            data = val;
            prev = nullptr;
            next = nullptr;
        }
    };

    Node *head;
    Node *tail;

public:
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    ~DoublyLinkedList() {
        Node *cur = head;

        while (cur != nullptr) {
            Node *next = cur->next;
            delete cur;
            cur = next;
        }
    }

    void insertAtBeginning(int val) {
        Node *newNode = new Node(val);

        if (head == nullptr) {
            head = tail = newNode;
            return;
        }

        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }

    void insertAtEnd(int val) {
        Node *newNode = new Node(val);

        if (tail == nullptr) {
            head = tail = newNode;
            return;
        }

        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    void deleteFromBeginning() {
        if (head == nullptr) {
            cout << "List is empty\n";
            return;
        }

        Node *temp = head;
        head = head->next;

        if (head != nullptr)
            head->prev = nullptr;
        else
            tail = nullptr;

        delete temp;
    }

    void deleteFromEnd() {
        if (tail == nullptr) {
            cout << "List is empty\n";
            return;
        }

        Node *temp = tail;
        tail = tail->prev;

        if (tail != nullptr)
            tail->next = nullptr;
        else
            head = nullptr;

        delete temp;
    }

    bool search(int val) {
        Node *cur = head;

        while (cur != nullptr) {
            if (cur->data == val)
                return true;

            cur = cur->next;
        }

        return false;
    }

    void forwardTraversal() {
        if (head == nullptr) {
            cout << "List is empty\n";
            return;
        }

        Node *cur = head;

        cout << "Forward Traversal: ";

        while (cur != nullptr) {
            cout << cur->data << " <-> ";
            cur = cur->next;
        }

        cout << "NULL\n";
    }

    void backwardTraversal() {
        if (tail == nullptr) {
            cout << "List is empty\n";
            return;
        }

        Node *cur = tail;

        cout << "Backward Traversal: ";

        while (cur != nullptr) {
            cout << cur->data << " <-> ";
            cur = cur->prev;
        }

        cout << "NULL\n";
    }

    void reverse() {
        Node *cur = head;

        while (cur != nullptr) {
            Node *temp = cur->prev;

            cur->prev = cur->next;
            cur->next = temp;

            cur = cur->prev;
        }

        Node *temp = head;
        head = tail;
        tail = temp;
    }
};

int main() {
    DoublyLinkedList list;
    int choice, val;

    do {
        cout << "\n--- Doubly Linked List Menu ---\n"
             << "1. Insert At Beginning\n"
             << "2. Insert At End\n"
             << "3. Delete From Beginning\n"
             << "4. Delete From End\n"
             << "5. Search Element\n"
             << "6. Forward Traversal\n"
             << "7. Backward Traversal\n"
             << "8. Reverse List\n"
             << "9. Exit\n"
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
                list.deleteFromBeginning();
                break;

            case 4:
                list.deleteFromEnd();
                break;

            case 5:
                cout << "Enter value to search: ";
                cin >> val;

                if (list.search(val))
                    cout << "Element found in list\n";
                else
                    cout << "Element not found\n";

                break;

            case 6:
                list.forwardTraversal();
                break;

            case 7:
                list.backwardTraversal();
                break;

            case 8:
                list.reverse();
                cout << "List reversed successfully\n";
                break;

            case 9:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice\n";
        }

    } while (choice != 9);

    return 0;
}