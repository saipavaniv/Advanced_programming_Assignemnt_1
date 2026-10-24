#include <iostream>
using namespace std;

// ---------------- NORMAL LINEAR QUEUE ----------------
class Queue {
private:
    int *arr;
    int capacity;
    int frontIndex, rearIndex;

public:
    Queue(int size) {
        capacity = size;
        arr = new int[capacity];
        frontIndex = 0;
        rearIndex = -1;
    }

    ~Queue() {
        delete[] arr;
    }

    bool isEmpty() {
        return rearIndex < frontIndex;
    }

    bool isFull() {
        return rearIndex == capacity - 1;
    }

    void enqueue(int value) {
        if (isFull()) {
            cout << "Queue Overflow\n";
            return;
        }

        arr[++rearIndex] = value;
        cout << value << " inserted into normal queue\n";
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow\n";
            return;
        }

        cout << arr[frontIndex++] << " removed from normal queue\n";

        // Reset pointers when queue becomes empty to reclaim initial space
        if (frontIndex > rearIndex) {
            frontIndex = 0;
            rearIndex = -1;
        }
    }

    void front() {
        if (isEmpty())
            cout << "Queue is empty\n";
        else
            cout << "Front element: " << arr[frontIndex] << "\n";
    }

    void rear() {
        if (isEmpty())
            cout << "Queue is empty\n";
        else
            cout << "Rear element: " << arr[rearIndex] << "\n";
    }

    void display() {
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return;
        }

        cout << "Normal Queue: ";
        for (int i = frontIndex; i <= rearIndex; i++)
            cout << arr[i] << " ";
        cout << "\n";
    }
};

// ---------------- CIRCULAR QUEUE ----------------
class CircularQueue {
private:
    int *arr;
    int capacity;
    int frontIndex, rearIndex;
    int count;

public:
    CircularQueue(int size) {
        capacity = size;
        arr = new int[capacity];
        frontIndex = 0;
        rearIndex = -1;
        count = 0;
    }

    ~CircularQueue() {
        delete[] arr;
    }

    bool isEmpty() {
        return count == 0;
    }

    bool isFull() {
        return count == capacity;
    }

    void enqueue(int value) {
        if (isFull()) {
            cout << "Circular Queue Overflow\n";
            return;
        }

        rearIndex = (rearIndex + 1) % capacity;
        arr[rearIndex] = value;
        count++;

        cout << value << " inserted into circular queue\n";
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Circular Queue Underflow\n";
            return;
        }

        cout << arr[frontIndex] << " removed from circular queue\n";
        frontIndex = (frontIndex + 1) % capacity;
        count--;
    }

    void front() {
        if (isEmpty())
            cout << "Circular Queue is empty\n";
        else
            cout << "Front element: " << arr[frontIndex] << "\n";
    }

    void rear() {
        if (isEmpty())
            cout << "Circular Queue is empty\n";
        else
            cout << "Rear element: " << arr[rearIndex] << "\n";
    }

    void display() {
        if (isEmpty()) {
            cout << "Circular Queue is empty\n";
            return;
        }

        cout << "Circular Queue: ";
        for (int i = 0; i < count; i++)
            cout << arr[(frontIndex + i) % capacity] << " ";

        cout << "\n";
    }
};

int main() {
    int n = 5;
    cout << "Initializing Queue and Circular Queue with capacity = " << n << "\n\n";

    cout << "=== 1. Testing Normal Linear Queue ===\n";
    Queue q(n);
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.display();

    q.front();
    q.rear();

    q.dequeue();
    q.display();

    cout << "\n=== 2. Testing Circular Queue Space Efficiency ===\n";
    CircularQueue cq(n);

    // Fill up circular queue
    cq.enqueue(10);
    cq.enqueue(20);
    cq.enqueue(30);
    cq.enqueue(40);
    cq.enqueue(50);
    cq.display();

    // Dequeue 2 elements from the front
    cq.dequeue();
    cq.dequeue();
    cq.display();

    // Enqueue 2 new elements (wraps around to reuse indices 0 and 1)
    cq.enqueue(60);
    cq.enqueue(70);

    cq.display();
    cq.front();
    cq.rear();

    return 0;
}