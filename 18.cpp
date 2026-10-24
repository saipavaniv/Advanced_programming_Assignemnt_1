#include <iostream>
using namespace std;

class WeightedGraph {
private:
    struct Edge {
        int u;
        int v;
        int weight;
    };

    int vertices;
    int edgeCount;

    int **matrix;
    Edge *edges;

    void swapEdges(Edge &a, Edge &b) {
        Edge temp = a;
        a = b;
        b = temp;
    }

    // Manual Insertion Sort for Kruskal's algorithm (no STL allowed)
    void sortEdges() {
        for (int i = 1; i < edgeCount; i++) {
            Edge key = edges[i];
            int j = i - 1;

            while (j >= 0 && edges[j].weight > key.weight) {
                edges[j + 1] = edges[j];
                j--;
            }

            edges[j + 1] = key;
        }
    }

    // Encapsulated Disjoint Set Data Structure (Union-Find)
    class DisjointSet {
    private:
        int *parent;
        int *rank;

    public:
        DisjointSet(int n) {
            parent = new int[n];
            rank = new int[n];

            for (int i = 0; i < n; i++) {
                parent[i] = i;
                rank[i] = 0;
            }
        }

        ~DisjointSet() {
            delete[] parent;
            delete[] rank;
        }

        // Path Compression
        int find(int x) {
            if (parent[x] != x)
                parent[x] = find(parent[x]);

            return parent[x];
        }

        // Union by Rank
        bool unite(int a, int b) {
            a = find(a);
            b = find(b);

            if (a == b)
                return false; // Cycle detected

            if (rank[a] < rank[b])
                parent[a] = b;
            else if (rank[a] > rank[b])
                parent[b] = a;
            else {
                parent[b] = a;
                rank[a]++;
            }

            return true;
        }
    };

public:
    WeightedGraph(int n, int m) {
        vertices = n;
        edgeCount = m;

        matrix = new int*[vertices];
        for (int i = 0; i < vertices; i++) {
            matrix[i] = new int[vertices];
            for (int j = 0; j < vertices; j++)
                matrix[i][j] = 0;
        }

        edges = new Edge[edgeCount];
    }

    ~WeightedGraph() {
        for (int i = 0; i < vertices; i++)
            delete[] matrix[i];

        delete[] matrix;
        delete[] edges;
    }

    void addEdge(int index, int u, int v, int weight) {
        if (index < 0 || index >= edgeCount) return;
        edges[index].u = u;
        edges[index].v = v;
        edges[index].weight = weight;

        matrix[u][v] = weight;
        matrix[v][u] = weight;
    }

    // Prim's Minimum Spanning Tree Algorithm
    void prim() {
        const int INF = 1000000000;

        int *key = new int[vertices];
        int *parent = new int[vertices];
        bool *used = new bool[vertices];

        for (int i = 0; i < vertices; i++) {
            key[i] = INF;
            parent[i] = -1;
            used[i] = false;
        }

        key[0] = 0; // Start growing tree from vertex 0

        for (int count = 0; count < vertices; count++) {
            int u = -1;

            for (int i = 0; i < vertices; i++) {
                if (!used[i] && (u == -1 || key[i] < key[u])) {
                    u = i;
                }
            }

            if (u == -1 || key[u] == INF)
                break;

            used[u] = true;

            for (int v = 0; v < vertices; v++) {
                if (matrix[u][v] > 0 && !used[v] && matrix[u][v] < key[v]) {
                    key[v] = matrix[u][v];
                    parent[v] = u;
                }
            }
        }

        int totalCost = 0;
        int selectedEdges = 0;

        cout << "========================================\n";
        cout << "         Prim's Algorithm MST          \n";
        cout << "========================================\n";

        for (int v = 1; v < vertices; v++) {
            if (parent[v] != -1) {
                cout << "Edge " << parent[v] << " - " << v << " : Weight = " << matrix[parent[v]][v] << "\n";
                totalCost += matrix[parent[v]][v];
                selectedEdges++;
            }
        }

        if (selectedEdges != vertices - 1)
            cout << "Graph is disconnected; MST does not exist.\n";
        else
            cout << "Total Minimum Spanning Tree Cost: " << totalCost << "\n";

        delete[] key;
        delete[] parent;
        delete[] used;
    }

    // Kruskal's Minimum Spanning Tree Algorithm
    void kruskal() {
        sortEdges(); // Step 1: Sort edges by weight

        DisjointSet set(vertices);

        int totalCost = 0;
        int selectedEdges = 0;

        cout << "\n========================================\n";
        cout << "       Kruskal's Algorithm MST         \n";
        cout << "========================================\n";

        for (int i = 0; i < edgeCount && selectedEdges < vertices - 1; i++) {
            if (set.unite(edges[i].u, edges[i].v)) {
                cout << "Edge " << edges[i].u << " - " << edges[i].v << " : Weight = " << edges[i].weight << "\n";
                totalCost += edges[i].weight;
                selectedEdges++;
            }
        }

        if (selectedEdges != vertices - 1)
            cout << "Graph is disconnected; MST does not exist.\n";
        else
            cout << "Total Minimum Spanning Tree Cost: " << totalCost << "\n";
    }
};

int main() {
    int n, m;

    cout << "Enter number of vertices: ";
    cin >> n;

    cout << "Enter number of edges: ";
    cin >> m;

    WeightedGraph graph(n, m);

    cout << "Enter each edge as: source destination weight\n";

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cout << "Edge " << i + 1 << ": ";
        cin >> u >> v >> w;
        graph.addEdge(i, u, v, w);
    }

    cout << "\n";
    graph.prim();
    graph.kruskal();

    return 0;
}