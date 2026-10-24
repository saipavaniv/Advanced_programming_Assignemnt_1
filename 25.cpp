#include <iostream>
#include <string>
using namespace std;

// ============================================================
// 1) ARRAY - Dynamic array for Searching & Sorting
// ============================================================
class MyArray {
private:
    int *arr;
    int size, capacity;

public:
    MyArray(int cap) { capacity = cap; size = 0; arr = new int[capacity]; }
    ~MyArray() { delete[] arr; }

    void insert(int val) {
        if (size == capacity) { cout << "Array is full\n"; return; }
        arr[size++] = val;
    }

    void display() {
        cout << "Array: ";
        for (int i = 0; i < size; i++) cout << arr[i] << " ";
        cout << "\n";
    }

    int linearSearch(int key) {
        for (int i = 0; i < size; i++) if (arr[i] == key) return i;
        return -1;
    }

    int binarySearch(int key) {
        int low = 0, high = size - 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (arr[mid] == key) return mid;
            else if (arr[mid] < key) low = mid + 1;
            else high = mid - 1;
        }
        return -1;
    }

    void bubbleSort() {
        for (int i = 0; i < size - 1; i++)
            for (int j = 0; j < size - 1 - i; j++)
                if (arr[j] > arr[j + 1]) { int t = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = t; }
    }
};

// ============================================================
// 2) STACK - Array Based
// ============================================================
class MyStack {
private:
    int *arr, capacity, top;

public:
    MyStack(int cap) { capacity = cap; arr = new int[capacity]; top = -1; }
    ~MyStack() { delete[] arr; }

    bool isEmpty() { return top == -1; }
    bool isFull() { return top == capacity - 1; }

    void push(int val) {
        if (isFull()) { cout << "Stack Overflow\n"; return; }
        arr[++top] = val;
    }

    void pop() {
        if (isEmpty()) { cout << "Stack Underflow\n"; return; }
        cout << "Popped: " << arr[top--] << "\n";
    }

    void display() {
        if (isEmpty()) { cout << "Stack is empty\n"; return; }
        cout << "Stack (top -> bottom): ";
        for (int i = top; i >= 0; i--) cout << arr[i] << " ";
        cout << "\n";
    }
};

// ============================================================
// 3) QUEUE - Base Class & Derived Circular Queue
// ============================================================
class MyQueue {
protected:
    int *arr, capacity, frontIdx, rearIdx, count;

public:
    MyQueue(int cap) { capacity = cap; arr = new int[capacity]; frontIdx = 0; rearIdx = -1; count = 0; }
    virtual ~MyQueue() { delete[] arr; }

    virtual bool isEmpty() { return count == 0; }
    virtual bool isFull() { return count == capacity; }

    virtual void enqueue(int val) {
        if (rearIdx == capacity - 1) { cout << "Queue Overflow\n"; return; }
        arr[++rearIdx] = val;
        count++;
    }

    virtual void dequeue() {
        if (isEmpty()) { cout << "Queue Underflow\n"; return; }
        cout << "Dequeued: " << arr[frontIdx++] << "\n";
        count--;
    }

    virtual void display() {
        if (isEmpty()) { cout << "Queue is empty\n"; return; }
        cout << "Queue: ";
        for (int i = frontIdx; i <= rearIdx; i++) cout << arr[i] << " ";
        cout << "\n";
    }
};

class MyCircularQueue : public MyQueue {
public:
    MyCircularQueue(int cap) : MyQueue(cap) {}

    void enqueue(int val) override {
        if (isFull()) { cout << "Circular Queue Overflow\n"; return; }
        rearIdx = (rearIdx + 1) % capacity;
        arr[rearIdx] = val;
        count++;
    }

    void dequeue() override {
        if (isEmpty()) { cout << "Circular Queue Underflow\n"; return; }
        cout << "Dequeued: " << arr[frontIdx] << "\n";
        frontIdx = (frontIdx + 1) % capacity;
        count--;
    }

    void display() override {
        if (isEmpty()) { cout << "Circular Queue is empty\n"; return; }
        cout << "Circular Queue: ";
        for (int i = 0; i < count; i++) cout << arr[(frontIdx + i) % capacity] << " ";
        cout << "\n";
    }
};

// ============================================================
// 4) SINGLY LINKED LIST
// ============================================================
struct LNode {
    int data;
    LNode *next;
    LNode(int val) { data = val; next = nullptr; }
};

class MyLinkedList {
private:
    LNode *head;

public:
    MyLinkedList() { head = nullptr; }
    ~MyLinkedList() {
        LNode *cur = head;
        while (cur) { LNode *n = cur->next; delete cur; cur = n; }
    }

    void insertAtBeginning(int val) { LNode *n = new LNode(val); n->next = head; head = n; }

    void insertAtEnd(int val) {
        LNode *n = new LNode(val);
        if (!head) { head = n; return; }
        LNode *cur = head;
        while (cur->next) cur = cur->next;
        cur->next = n;
    }

    void deleteValue(int val) {
        if (!head) { cout << "List is empty\n"; return; }
        if (head->data == val) { LNode *t = head; head = head->next; delete t; return; }
        LNode *cur = head;
        while (cur->next && cur->next->data != val) cur = cur->next;
        if (!cur->next) { cout << "Value not found\n"; return; }
        LNode *t = cur->next; cur->next = t->next; delete t;
    }

    void reverse() {
        LNode *prev = nullptr, *cur = head, *next;
        while (cur) { next = cur->next; cur->next = prev; prev = cur; cur = next; }
        head = prev;
    }

    void display() {
        if (!head) { cout << "List is empty\n"; return; }
        LNode *cur = head;
        while (cur) { cout << cur->data << " -> "; cur = cur->next; }
        cout << "NULL\n";
    }
};

// ============================================================
// 5) BINARY TREE AND BINARY SEARCH TREE (BST)
// ============================================================
struct TNode {
    int data;
    TNode *left, *right;
    TNode(int val) { data = val; left = right = nullptr; }
};

class MyBinaryTree {
protected:
    TNode *root;

    void inorderHelper(TNode *n) { if (!n) return; inorderHelper(n->left); cout << n->data << " "; inorderHelper(n->right); }
    void preorderHelper(TNode *n) { if (!n) return; cout << n->data << " "; preorderHelper(n->left); preorderHelper(n->right); }
    void postorderHelper(TNode *n) { if (!n) return; postorderHelper(n->left); postorderHelper(n->right); cout << n->data << " "; }
    void destroy(TNode *n) { if (!n) return; destroy(n->left); destroy(n->right); delete n; }

public:
    MyBinaryTree() { root = nullptr; }
    virtual ~MyBinaryTree() { destroy(root); }

    virtual void insert(int val) {
        TNode **cur = &root;
        while (*cur) cur = (val < (*cur)->data) ? &(*cur)->left : &(*cur)->right;
        *cur = new TNode(val);
    }

    void preorder() { cout << "Preorder: "; preorderHelper(root); cout << "\n"; }
    void inorder() { cout << "Inorder: "; inorderHelper(root); cout << "\n"; }
    void postorder() { cout << "Postorder: "; postorderHelper(root); cout << "\n"; }

    void levelOrder() {
        if (!root) { cout << "Tree is empty\n"; return; }
        TNode *queue[100]; int front = 0, rear = 0;
        queue[rear++] = root;
        cout << "Level-order: ";
        while (front < rear) {
            TNode *cur = queue[front++];
            cout << cur->data << " ";
            if (cur->left) queue[rear++] = cur->left;
            if (cur->right) queue[rear++] = cur->right;
        }
        cout << "\n";
    }
};

class MyBST : public MyBinaryTree {
private:
    TNode* deleteHelper(TNode *node, int val) {
        if (!node) return nullptr;
        if (val < node->data) node->left = deleteHelper(node->left, val);
        else if (val > node->data) node->right = deleteHelper(node->right, val);
        else {
            if (!node->left && !node->right) { delete node; return nullptr; }
            if (!node->left) { TNode *t = node->right; delete node; return t; }
            if (!node->right) { TNode *t = node->left; delete node; return t; }
            TNode *succ = node->right;
            while (succ->left) succ = succ->left;
            node->data = succ->data;
            node->right = deleteHelper(node->right, succ->data);
        }
        return node;
    }

public:
    void insert(int val) override {
        TNode **cur = &root;
        while (*cur) {
            if (val == (*cur)->data) { cout << "Duplicate ignored\n"; return; }
            cur = (val < (*cur)->data) ? &(*cur)->left : &(*cur)->right;
        }
        *cur = new TNode(val);
    }

    bool search(int val) {
        TNode *cur = root;
        while (cur) {
            if (cur->data == val) return true;
            cur = (val < cur->data) ? cur->left : cur->right;
        }
        return false;
    }

    void remove(int val) { root = deleteHelper(root, val); }
};

// ============================================================
// 6) MAX HEAP
// ============================================================
class MyMaxHeap {
private:
    int *arr, size, capacity;
    void swapValues(int i, int j) { int t = arr[i]; arr[i] = arr[j]; arr[j] = t; }

    void heapifyDown(int i) {
        int best = i, l = 2 * i + 1, r = 2 * i + 2;
        if (l < size && arr[l] > arr[best]) best = l;
        if (r < size && arr[r] > arr[best]) best = r;
        if (best != i) { swapValues(i, best); heapifyDown(best); }
    }

public:
    MyMaxHeap(int cap) { capacity = cap; size = 0; arr = new int[capacity]; }
    ~MyMaxHeap() { delete[] arr; }

    void insert(int val) {
        if (size == capacity) { cout << "Heap is full\n"; return; }
        int i = size++;
        arr[i] = val;
        while (i > 0 && arr[i] > arr[(i - 1) / 2]) { swapValues(i, (i - 1) / 2); i = (i - 1) / 2; }
    }

    void deleteMax() {
        if (size == 0) { cout << "Heap is empty\n"; return; }
        cout << "Deleted max: " << arr[0] << "\n";
        arr[0] = arr[--size];
        heapifyDown(0);
    }

    void display() {
        cout << "Heap: ";
        for (int i = 0; i < size; i++) cout << arr[i] << " ";
        cout << "\n";
    }
};

// ============================================================
// 7) GRAPH - Adjacency List (BFS & DFS)
// ============================================================
struct GNode { int vertex; GNode *next; GNode(int v) { vertex = v; next = nullptr; } };

class MyGraph {
private:
    int V;
    GNode **adj;

    void addToList(int u, int v) {
        GNode *n = new GNode(v);
        if (!adj[u]) { adj[u] = n; return; }
        GNode *cur = adj[u];
        while (cur->next) cur = cur->next;
        cur->next = n;
    }

public:
    MyGraph(int vertices) {
        V = vertices;
        adj = new GNode*[V];
        for (int i = 0; i < V; i++) adj[i] = nullptr;
    }
    ~MyGraph() {
        for (int i = 0; i < V; i++) {
            GNode *cur = adj[i];
            while (cur) { GNode *n = cur->next; delete cur; cur = n; }
        }
        delete[] adj;
    }

    void addEdge(int u, int v) { addToList(u, v); addToList(v, u); }

    void display() {
        for (int i = 0; i < V; i++) {
            cout << i << " -> ";
            for (GNode *cur = adj[i]; cur; cur = cur->next) cout << cur->vertex << " ";
            cout << "\n";
        }
    }

    void bfs(int start) {
        bool *visited = new bool[V]();
        int *queue = new int[V]; int front = 0, rear = 0;
        visited[start] = true;
        queue[rear++] = start;
        cout << "BFS: ";
        while (front < rear) {
            int u = queue[front++];
            cout << u << " ";
            for (GNode *cur = adj[u]; cur; cur = cur->next)
                if (!visited[cur->vertex]) { visited[cur->vertex] = true; queue[rear++] = cur->vertex; }
        }
        cout << "\n";
        delete[] visited; delete[] queue;
    }

    void dfsHelper(int u, bool visited[]) {
        visited[u] = true;
        cout << u << " ";
        for (GNode *cur = adj[u]; cur; cur = cur->next)
            if (!visited[cur->vertex]) dfsHelper(cur->vertex, visited);
    }

    void dfs(int start) {
        bool *visited = new bool[V]();
        cout << "DFS: ";
        dfsHelper(start, visited);
        cout << "\n";
        delete[] visited;
    }
};

// ============================================================
// MENU HANDLERS
// ============================================================
void searchingMenu() {
    int n; cout << "How many elements? "; cin >> n;
    MyArray a(n);
    cout << "Enter elements: ";
    for (int i = 0, v; i < n; i++) { cin >> v; a.insert(v); }
    a.display();
    a.bubbleSort();
    cout << "(Sorted for Binary Search) "; a.display();
    int key; cout << "Search for key: "; cin >> key;
    int pos = a.binarySearch(key);
    cout << (pos != -1 ? "Found at index " + to_string(pos) : "Not found") << "\n";
}

void sortingMenu() {
    int n; cout << "How many elements? "; cin >> n;
    MyArray a(n);
    cout << "Enter elements: ";
    for (int i = 0, v; i < n; i++) { cin >> v; a.insert(v); }
    cout << "Before: "; a.display();
    a.bubbleSort();
    cout << "After: "; a.display();
}

void stackMenu() {
    int cap; cout << "Stack capacity: "; cin >> cap;
    MyStack s(cap);
    int choice, val;
    do {
        cout << "\n--- STACK MENU ---\n1. Push\n2. Pop\n3. Display\n4. Back\nChoice: "; cin >> choice;
        if (choice == 1) { cout << "Value: "; cin >> val; s.push(val); }
        else if (choice == 2) s.pop();
        else if (choice == 3) s.display();
    } while (choice != 4);
}

void queueMenu() {
    int cap; cout << "Queue capacity: "; cin >> cap;
    MyCircularQueue q(cap);
    int choice, val;
    do {
        cout << "\n--- CIRCULAR QUEUE MENU ---\n1. Enqueue\n2. Dequeue\n3. Display\n4. Back\nChoice: "; cin >> choice;
        if (choice == 1) { cout << "Value: "; cin >> val; q.enqueue(val); }
        else if (choice == 2) q.dequeue();
        else if (choice == 3) q.display();
    } while (choice != 4);
}

void linkedListMenu() {
    MyLinkedList list;
    int choice, val;
    do {
        cout << "\n--- LINKED LIST MENU ---\n1. Insert Beg\n2. Insert End\n3. Delete Value\n4. Reverse\n5. Display\n6. Back\nChoice: ";
        cin >> choice;
        if (choice == 1) { cout << "Value: "; cin >> val; list.insertAtBeginning(val); }
        else if (choice == 2) { cout << "Value: "; cin >> val; list.insertAtEnd(val); }
        else if (choice == 3) { cout << "Value: "; cin >> val; list.deleteValue(val); }
        else if (choice == 4) list.reverse();
        else if (choice == 5) list.display();
    } while (choice != 6);
}

void binaryTreeMenu() {
    MyBinaryTree tree;
    int choice, val;
    do {
        cout << "\n--- BINARY TREE MENU ---\n1. Insert\n2. Preorder\n3. Inorder\n4. Postorder\n5. Level-order\n6. Back\nChoice: ";
        cin >> choice;
        if (choice == 1) { cout << "Value: "; cin >> val; tree.insert(val); }
        else if (choice == 2) tree.preorder();
        else if (choice == 3) tree.inorder();
        else if (choice == 4) tree.postorder();
        else if (choice == 5) tree.levelOrder();
    } while (choice != 6);
}

void bstMenu() {
    MyBST tree;
    int choice, val;
    do {
        cout << "\n--- BST MENU ---\n1. Insert\n2. Search\n3. Delete\n4. Inorder\n5. Back\nChoice: ";
        cin >> choice;
        if (choice == 1) { cout << "Value: "; cin >> val; tree.insert(val); }
        else if (choice == 2) { cout << "Value: "; cin >> val; cout << (tree.search(val) ? "Found\n" : "Not Found\n"); }
        else if (choice == 3) { cout << "Value: "; cin >> val; tree.remove(val); }
        else if (choice == 4) tree.inorder();
    } while (choice != 5);
}

void heapMenu() {
    int cap; cout << "Heap capacity: "; cin >> cap;
    MyMaxHeap heap(cap);
    int choice, val;
    do {
        cout << "\n--- HEAP MENU ---\n1. Insert\n2. Delete Max\n3. Display\n4. Back\nChoice: "; cin >> choice;
        if (choice == 1) { cout << "Value: "; cin >> val; heap.insert(val); }
        else if (choice == 2) heap.deleteMax();
        else if (choice == 3) heap.display();
    } while (choice != 4);
}

void graphMenu() {
    int v; cout << "Number of vertices: "; cin >> v;
    MyGraph g(v);
    int choice, u, w;
    do {
        cout << "\n--- GRAPH MENU ---\n1. Add Edge\n2. Display\n3. BFS\n4. DFS\n5. Back\nChoice: "; cin >> choice;
        if (choice == 1) { cout << "u v: "; cin >> u >> w; g.addEdge(u, w); }
        else if (choice == 2) g.display();
        else if (choice == 3) { cout << "Start vertex: "; cin >> u; g.bfs(u); }
        else if (choice == 4) { cout << "Start vertex: "; cin >> u; g.dfs(u); }
    } while (choice != 5);
}

// ============================================================
// MAIN APPLICATION
// ============================================================
int main() {
    int choice;
    do {
        cout << "\n========================================\n"
             << "            DSA LIBRARY MENU            \n"
             << "========================================\n"
             << "1. Searching\n2. Sorting\n3. Stack\n4. Queue\n5. Linked List\n"
             << "6. Binary Tree\n7. Binary Search Tree\n8. Heap\n9. Graph\n10. Exit\n"
             << "Enter Choice: ";
        cin >> choice;
        switch (choice) {
            case 1: searchingMenu(); break;
            case 2: sortingMenu(); break;
            case 3: stackMenu(); break;
            case 4: queueMenu(); break;
            case 5: linkedListMenu(); break;
            case 6: binaryTreeMenu(); break;
            case 7: bstMenu(); break;
            case 8: heapMenu(); break;
            case 9: graphMenu(); break;
            case 10: cout << "Exiting DSA Library...\n"; break;
            default: cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 10);
    return 0;
}