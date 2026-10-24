#include <iostream>
using namespace std;

class Heap {
protected:
    int *arr;
    int size;
    int capacity;

    // Defines whether larger or smaller value has higher priority
    virtual bool higher(int a, int b) = 0;

    void swapValues(int i, int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

public:
    Heap(int cap) {
        capacity = cap;
        size = 0;
        arr = new int[capacity];
    }

    virtual ~Heap() {
        delete[] arr;
    }

    // Restore heap property downward
    void heapify(int n, int i) {
        int best = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && higher(arr[left], arr[best]))
            best = left;

        if (right < n && higher(arr[right], arr[best]))
            best = right;

        if (best != i) {
            swapValues(i, best);
            heapify(n, best);
        }
    }

    // Insert an element
    void insert(int value) {
        if (size == capacity) {
            cout << "Heap is full\n";
            return;
        }

        int i = size;
        arr[size] = value;
        size++;

        // Move the new element upward
        while (i > 0 && higher(arr[i], arr[(i - 1) / 2])) {
            swapValues(i, (i - 1) / 2);
            i = (i - 1) / 2;
        }
    }

    // Delete the root element
    int deleteTop() {
        if (size == 0) {
            cout << "Heap is empty\n";
            return -1;
        }

        int top = arr[0];

        arr[0] = arr[size - 1];
        size--;

        if (size > 0)
            heapify(size, 0);

        return top;
    }

    // Build heap from an array
    void buildHeap(int input[], int n) {
        if (n > capacity) {
            cout << "Input size exceeds heap capacity\n";
            return;
        }

        size = n;

        for (int i = 0; i < n; i++)
            arr[i] = input[i];

        // Start from last non-leaf node
        for (int i = size / 2 - 1; i >= 0; i--)
            heapify(size, i);
    }

    // Display heap
    void display() {
        for (int i = 0; i < size; i++)
            cout << arr[i] << " ";

        cout << "\n";
    }
};


// ================= MAX HEAP =================

class MaxHeap : public Heap {
protected:
    bool higher(int a, int b) override {
        return a > b;
    }

public:
    MaxHeap(int cap) : Heap(cap) {}

    int deleteMaximum() {
        return deleteTop();
    }

    // Heap Sort using Max Heap
    void heapSort(int input[], int n) {
        if (n > capacity) {
            cout << "Input size exceeds heap capacity\n";
            return;
        }

        buildHeap(input, n);

        // Move maximum element to the end
        for (int i = size - 1; i > 0; i--) {
            swapValues(0, i);
            heapify(i, 0);
        }

        cout << "Sorted Array (Ascending): ";

        for (int i = 0; i < n; i++)
            cout << arr[i] << " ";

        cout << "\n";

        size = 0;
    }
};


// ================= MIN HEAP =================

class MinHeap : public Heap {
protected:
    bool higher(int a, int b) override {
        return a < b;
    }

public:
    MinHeap(int cap) : Heap(cap) {}

    int deleteMinimum() {
        return deleteTop();
    }
};


// ================= MAIN =================

int main() {
    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    if (n <= 0) {
        cout << "Invalid number of elements\n";
        return 0;
    }

    int *data = new int[n];

    cout << "Enter elements: ";
    for (int i = 0; i < n; i++)
        cin >> data[i];


    // -------- MAX HEAP --------

    cout << "\n=== Max Heap ===\n";

    MaxHeap maxHeap(n + 10);

    maxHeap.buildHeap(data, n);

    cout << "Built Max Heap: ";
    maxHeap.display();

    int value;

    cout << "Enter value to insert into Max Heap: ";
    cin >> value;

    maxHeap.insert(value);

    cout << "After insertion: ";
    maxHeap.display();

    cout << "Deleted Maximum: "
         << maxHeap.deleteMaximum() << "\n";

    cout << "Max Heap after deletion: ";
    maxHeap.display();


    // -------- MIN HEAP --------

    cout << "\n=== Min Heap ===\n";

    MinHeap minHeap(n + 10);

    minHeap.buildHeap(data, n);

    cout << "Built Min Heap: ";
    minHeap.display();

    cout << "Deleted Minimum: "
         << minHeap.deleteMinimum() << "\n";

    cout << "Min Heap after deletion: ";
    minHeap.display();


    // -------- HEAP SORT --------

    cout << "\n=== Heap Sort ===\n";

    MaxHeap sortHeap(n);

    sortHeap.heapSort(data, n);


    delete[] data;

    return 0;
}