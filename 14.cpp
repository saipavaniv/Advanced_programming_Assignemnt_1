#include <iostream>
using namespace std;

class PriorityQueue {
private:
    struct Item {
        int value;
        int priority;
    };

    Item *heap;
    int size;
    int capacity;

    void swapItems(Item &a, Item &b) {
        Item temp = a;
        a = b;
        b = temp;
    }

    // Restore max-heap property upward
    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;

            if (heap[parent].priority >= heap[index].priority)
                break;

            swapItems(heap[parent], heap[index]);
            index = parent;
        }
    }

    // Restore max-heap property downward
    void heapifyDown(int index) {
        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = index;

            if (left < size &&
                heap[left].priority > heap[largest].priority)
                largest = left;

            if (right < size &&
                heap[right].priority > heap[largest].priority)
                largest = right;

            if (largest == index)
                break;

            swapItems(heap[index], heap[largest]);
            index = largest;
        }
    }

public:
    PriorityQueue(int cap) {
        capacity = cap;
        size = 0;
        heap = new Item[capacity];
    }

    ~PriorityQueue() {
        delete[] heap;
    }

    // 1. Insert element with priority
    void insert(int value, int priority) {
        if (size == capacity) {
            cout << "Priority Queue Overflow\n";
            return;
        }

        heap[size].value = value;
        heap[size].priority = priority;

        size++;
        heapifyUp(size - 1);
    }

    // 2. Remove highest-priority element
    bool removeHighest(int &value, int &priority) {
        if (size == 0) {
            cout << "Priority Queue Underflow\n";
            return false;
        }

        value = heap[0].value;
        priority = heap[0].priority;

        heap[0] = heap[size - 1];
        size--;

        if (size > 0)
            heapifyDown(0);

        return true;
    }

    // 3. Peek at highest-priority element
    bool peek(int &value, int &priority) {
        if (size == 0)
            return false;

        value = heap[0].value;
        priority = heap[0].priority;

        return true;
    }

    // 4. Display all elements
    void display() {
        if (size == 0) {
            cout << "Priority Queue is empty\n";
            return;
        }

        cout << "Priority Queue: ";

        for (int i = 0; i < size; i++) {
            cout << "(Value=" << heap[i].value
                 << ", Priority=" << heap[i].priority << ") ";
        }

        cout << "\n";
    }
};

int main() {
    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    if (n <= 0) {
        cout << "Invalid number of elements\n";
        return 0;
    }

    PriorityQueue pq(n);

    cout << "Enter value and priority for each element:\n";

    for (int i = 0; i < n; i++) {
        int value, priority;

        cout << "Element " << i + 1 << ": ";
        cin >> value >> priority;

        pq.insert(value, priority);
    }

    cout << "\n=== Priority Queue ===\n";
    pq.display();

    int value, priority;

    cout << "\n=== Peek ===\n";

    if (pq.peek(value, priority)) {
        cout << "Highest Priority Element: "
             << "Value = " << value
             << ", Priority = " << priority << "\n";
    }

    cout << "\n=== Removing Highest-Priority Elements ===\n";

    while (pq.removeHighest(value, priority)) {
        cout << "Removed: "
             << "Value = " << value
             << ", Priority = " << priority << "\n";
    }

    return 0;
}