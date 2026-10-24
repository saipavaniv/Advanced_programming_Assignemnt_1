#include <iostream>
using namespace std;

// Base Graph Class
class Graph {
protected:
    int vertices;
    bool directed;

    // Dynamic Adjacency Matrix
    int **matrix;

    // Node for Adjacency List
    struct EdgeNode {
        int vertex;
        EdgeNode *next;

        EdgeNode(int v) {
            vertex = v;
            next = nullptr;
        }
    };

    // Dynamic Adjacency List
    EdgeNode **list;

    void addListEdge(int u, int v) {
        EdgeNode *newNode = new EdgeNode(v);
        // Prepend to list for O(1) insertion
        newNode->next = list[u];
        list[u] = newNode;
    }

public:
    Graph(int n, bool isDirected = false) {
        vertices = n;
        directed = isDirected;

        // Allocate dynamic 2D matrix
        matrix = new int*[vertices];
        for (int i = 0; i < vertices; i++) {
            matrix[i] = new int[vertices];
            for (int j = 0; j < vertices; j++)
                matrix[i][j] = 0;
        }

        // Allocate dynamic adjacency list
        list = new EdgeNode*[vertices];
        for (int i = 0; i < vertices; i++)
            list[i] = nullptr;
    }

    virtual ~Graph() {
        for (int i = 0; i < vertices; i++) {
            EdgeNode *current = list[i];
            while (current != nullptr) {
                EdgeNode *temp = current;
                current = current->next;
                delete temp;
            }
            delete[] matrix[i];
        }
        delete[] matrix;
        delete[] list;
    }

    void addEdge(int u, int v) {
        if (u < 0 || v < 0 || u >= vertices || v >= vertices) return;

        matrix[u][v] = 1;
        addListEdge(u, v);

        if (!directed) {
            matrix[v][u] = 1;
            addListEdge(v, u);
        }
    }

    void displayGraph() {
        cout << "Adjacency List Structure:\n";
        for (int i = 0; i < vertices; i++) {
            cout << "Vertex " << i << " -> ";
            EdgeNode *current = list[i];
            while (current != nullptr) {
                cout << current->vertex << " ";
                current = current->next;
            }
            cout << "\n";
        }
    }
};

// Extended Class as required: Question 16 ("Extend your Graph class")
class GraphTraversal : public Graph {
private:
    void dfsRecursive(int current, bool visited[]) {
        visited[current] = true;
        cout << current << " ";

        // Traverse neighbors using the adjacency list
        EdgeNode *neighbor = list[current];
        while (neighbor != nullptr) {
            if (!visited[neighbor->vertex]) {
                dfsRecursive(neighbor->vertex, visited);
            }
            neighbor = neighbor->next;
        }
    }

public:
    GraphTraversal(int n, bool isDirected = false) : Graph(n, isDirected) {}

    // Breadth-First Search (BFS) using a dynamic FIFO queue
    void BFS(int start) {
        if (start < 0 || start >= vertices) return;

        bool *visited = new bool[vertices];
        for (int i = 0; i < vertices; i++) visited[i] = false;

        int *queue = new int[vertices];
        int front = 0, rear = 0;

        visited[start] = true;
        queue[rear++] = start;

        cout << "BFS Traversal Order (starting at " << start << "): ";

        while (front < rear) {
            int current = queue[front++];
            cout << current << " ";

            EdgeNode *neighbor = list[current];
            while (neighbor != nullptr) {
                if (!visited[neighbor->vertex]) {
                    visited[neighbor->vertex] = true;
                    queue[rear++] = neighbor->vertex;
                }
                neighbor = neighbor->next;
            }
        }
        cout << "\n";

        delete[] queue;
        delete[] visited;
    }

    // Depth-First Search (DFS) using recursion (Call Stack)
    void DFS(int start) {
        if (start < 0 || start >= vertices) return;

        bool *visited = new bool[vertices];
        for (int i = 0; i < vertices; i++) visited[i] = false;

        cout << "DFS Traversal Order (starting at " << start << "): ";
        dfsRecursive(start, visited);
        cout << "\n";

        delete[] visited;
    }
};

int main() {
    // Constructing the exact graph given in Question 16:
    // Vertices: 6 (0 to 5)
    // Edges: (0-1), (0-2), (1-3), (1-4), (2-5)
    GraphTraversal g(6, false);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);

    cout << "=== Graph Structure ===\n";
    g.displayGraph();

    cout << "\n=== Graph Traversals ===\n";
    g.BFS(0);
    g.DFS(0);

    return 0;
}