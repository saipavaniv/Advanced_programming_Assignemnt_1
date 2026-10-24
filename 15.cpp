#include <iostream>
using namespace std;

class Graph {
private:
    int maxVertices;
    int vertices;
    bool directed;

    // Adjacency Matrix
    int **matrix;

    // Node for Adjacency List
    struct EdgeNode {
        int vertex;
        int weight;
        EdgeNode *next;

        EdgeNode(int v, int w) {
            vertex = v;
            weight = w;
            next = nullptr;
        }
    };

    // Adjacency List
    EdgeNode **list;

    // Check whether an edge already exists
    bool edgeExists(int u, int v) {
        EdgeNode *current = list[u];

        while (current != nullptr) {
            if (current->vertex == v)
                return true;

            current = current->next;
        }

        return false;
    }

    // Add edge to adjacency list
    void addListEdge(int u, int v, int weight) {
        EdgeNode *newNode = new EdgeNode(v, weight);
        newNode->next = list[u];
        list[u] = newNode;
    }

    // Remove edge from adjacency list
    void removeListEdge(int u, int v) {
        EdgeNode *current = list[u];
        EdgeNode *previous = nullptr;

        while (current != nullptr && current->vertex != v) {
            previous = current;
            current = current->next;
        }

        if (current == nullptr)
            return;

        if (previous == nullptr)
            list[u] = current->next;
        else
            previous->next = current->next;

        delete current;
    }

    // Delete all adjacency-list nodes
    void clearList() {
        for (int i = 0; i < maxVertices; i++) {
            EdgeNode *current = list[i];

            while (current != nullptr) {
                EdgeNode *temp = current;
                current = current->next;
                delete temp;
            }

            list[i] = nullptr;
        }
    }

public:
    // Constructor
    Graph(int maxV, bool isDirected) {
        maxVertices = maxV;
        vertices = 0;
        directed = isDirected;

        // Allocate adjacency matrix
        matrix = new int*[maxVertices];

        for (int i = 0; i < maxVertices; i++) {
            matrix[i] = new int[maxVertices];

            for (int j = 0; j < maxVertices; j++)
                matrix[i][j] = 0;
        }

        // Allocate adjacency list
        list = new EdgeNode*[maxVertices];

        for (int i = 0; i < maxVertices; i++)
            list[i] = nullptr;
    }

    // Destructor
    ~Graph() {
        clearList();

        for (int i = 0; i < maxVertices; i++)
            delete[] matrix[i];

        delete[] matrix;
        delete[] list;
    }

    // Add Vertex
    void addVertex() {
        if (vertices == maxVertices) {
            cout << "Maximum vertex capacity reached.\n";
            return;
        }

        cout << "Vertex " << vertices << " added.\n";
        vertices++;
    }

    // Add Edge
    void addEdge(int u, int v, int weight = 1) {
        if (u < 0 || v < 0 || u >= vertices || v >= vertices) {
            cout << "Invalid vertex index.\n";
            return;
        }

        if (u == v) {
            cout << "Self-loops are not allowed.\n";
            return;
        }

        if (edgeExists(u, v)) {
            cout << "Edge already exists.\n";
            return;
        }

        // Add to adjacency matrix
        matrix[u][v] = weight;

        // Add to adjacency list
        addListEdge(u, v, weight);

        // For undirected graph, add both directions
        if (!directed) {
            matrix[v][u] = weight;
            addListEdge(v, u, weight);
        }
    }

    // Remove Edge
    void removeEdge(int u, int v) {
        if (u < 0 || v < 0 || u >= vertices || v >= vertices) {
            cout << "Invalid vertex index.\n";
            return;
        }

        if (!edgeExists(u, v)) {
            cout << "Edge does not exist.\n";
            return;
        }

        matrix[u][v] = 0;
        removeListEdge(u, v);

        // For undirected graph, remove both directions
        if (!directed) {
            matrix[v][u] = 0;
            removeListEdge(v, u);
        }
    }

    // Display graph
    void displayGraph() {
        cout << "\n========================================\n";

        if (directed)
            cout << "DIRECTED GRAPH";
        else
            cout << "UNDIRECTED GRAPH";

        cout << " (" << vertices << " Vertices)\n";
        cout << "========================================\n";

        // Display Adjacency Matrix
        cout << "\nAdjacency Matrix:\n\n";

        cout << "    ";

        for (int i = 0; i < vertices; i++)
            cout << i << " ";

        cout << "\n";

        for (int i = 0; i < vertices; i++) {
            cout << i << " : ";

            for (int j = 0; j < vertices; j++)
                cout << matrix[i][j] << " ";

            cout << "\n";
        }

        // Display Adjacency List
        cout << "\nAdjacency List:\n";

        for (int i = 0; i < vertices; i++) {
            cout << i << " -> ";

            EdgeNode *current = list[i];

            while (current != nullptr) {
                cout << current->vertex
                     << "(w=" << current->weight << ")";

                if (current->next != nullptr)
                    cout << " -> ";

                current = current->next;
            }

            cout << "\n";
        }

        cout << "========================================\n";
    }
};

int main() {
    int maxVertices;
    int directedChoice;

    cout << "Enter maximum number of vertices: ";
    cin >> maxVertices;

    if (maxVertices <= 0) {
        cout << "Invalid number of vertices.\n";
        return 0;
    }

    cout << "Enter 1 for Directed Graph or 0 for Undirected Graph: ";
    cin >> directedChoice;

    if (directedChoice != 0 && directedChoice != 1) {
        cout << "Invalid choice.\n";
        return 0;
    }

    Graph graph(maxVertices, directedChoice == 1);

    int numberOfVertices;

    cout << "Enter number of vertices: ";
    cin >> numberOfVertices;

    if (numberOfVertices <= 0 || numberOfVertices > maxVertices) {
        cout << "Invalid number of vertices.\n";
        return 0;
    }

    // Add vertices
    for (int i = 0; i < numberOfVertices; i++)
        graph.addVertex();

    int numberOfEdges;

    cout << "\nEnter number of edges: ";
    cin >> numberOfEdges;

    if (numberOfEdges < 0) {
        cout << "Invalid number of edges.\n";
        return 0;
    }

    // Add edges
    cout << "Enter each edge as: source destination weight\n";

    for (int i = 0; i < numberOfEdges; i++) {
        int u, v, weight;

        cout << "Edge " << i + 1 << ": ";
        cin >> u >> v >> weight;

        graph.addEdge(u, v, weight);
    }

    // Display graph
    cout << "\n=== Graph Before Removing Edge ===";
    graph.displayGraph();

    // Remove an edge
    char choice;

    cout << "\nDo you want to remove an edge? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        int u, v;

        cout << "Enter source and destination of edge to remove: ";
        cin >> u >> v;

        graph.removeEdge(u, v);

        cout << "\n=== Graph After Removing Edge ===";
        graph.displayGraph();
    }

    return 0;
}