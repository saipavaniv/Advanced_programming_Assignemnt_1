#include <iostream>
#include <limits>
using namespace std;

class WeightedGraph {
private:
    int vertices;
    int **weight; // Dynamic 2D matrix for edge weights

    // Finds unvisited vertex with minimum tentative distance
    int findMinimumVertex(int distance[], bool visited[]) {
        int minimumVertex = -1;

        for (int i = 0; i < vertices; i++) {
            if (!visited[i]) {
                if (minimumVertex == -1 || distance[i] < distance[minimumVertex]) {
                    minimumVertex = i;
                }
            }
        }

        return minimumVertex;
    }

    // Recursively prints path from source to target vertex
    void printPath(int parent[], int vertex) {
        if (vertex == -1)
            return;

        if (parent[vertex] != -1) {
            printPath(parent, parent[vertex]);
            cout << " -> ";
        }

        cout << vertex;
    }

public:
    WeightedGraph(int n) {
        vertices = n;
        weight = new int*[vertices];

        for (int i = 0; i < vertices; i++) {
            weight[i] = new int[vertices];
            for (int j = 0; j < vertices; j++)
                weight[i][j] = 0; // 0 weight indicates no edge
        }
    }

    ~WeightedGraph() {
        for (int i = 0; i < vertices; i++)
            delete[] weight[i];
        delete[] weight;
    }

    void addEdge(int u, int v, int w) {
        if (u < 0 || v < 0 || u >= vertices || v >= vertices) return;
        weight[u][v] = w;
        weight[v][u] = w;
    }

    void dijkstra(int source) {
        if (source < 0 || source >= vertices) {
            cout << "Invalid source vertex!\n";
            return;
        }

        // Safe infinity value to prevent integer overflow during addition
        const int INF = numeric_limits<int>::max() / 4;

        int *distance = new int[vertices];
        int *parent = new int[vertices];
        bool *visited = new bool[vertices];

        for (int i = 0; i < vertices; i++) {
            distance[i] = INF;
            parent[i] = -1;
            visited[i] = false;
        }

        distance[source] = 0;

        for (int count = 0; count < vertices; count++) {
            int u = findMinimumVertex(distance, visited);

            if (u == -1 || distance[u] == INF)
                break; // Remaining vertices are unreachable

            visited[u] = true;

            // Relaxation step
            for (int v = 0; v < vertices; v++) {
                if (weight[u][v] > 0 && !visited[v] && 
                    distance[u] + weight[u][v] < distance[v]) {

                    distance[v] = distance[u] + weight[u][v];
                    parent[v] = u;
                }
            }
        }

        // Print formatted output table
        cout << "\n======================================================\n";
        cout << " Shortest Paths from Source Vertex (" << source << ")\n";
        cout << "======================================================\n";
        cout << "Target Node\tMin Distance\tShortest Path\n";
        cout << "------------------------------------------------------\n";

        for (int v = 0; v < vertices; v++) {
            cout << "    " << v << "\t\t";

            if (distance[v] == INF) {
                cout << "INF\t\tNo Path Exists\n";
            } else {
                cout << distance[v] << "\t\t";
                printPath(parent, v);
                cout << "\n";
            }
        }
        cout << "======================================================\n";

        delete[] distance;
        delete[] parent;
        delete[] visited;
    }
};

int main() {
    int n, m;

    cout << "Enter number of vertices: ";
    cin >> n;

    if (n <= 0) return 0;

    WeightedGraph graph(n);

    cout << "Enter number of edges: ";
    cin >> m;

    cout << "Enter each edge as: source destination weight\n";
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cout << "Edge " << i + 1 << ": ";
        cin >> u >> v >> w;
        graph.addEdge(u, v, w);
    }

    int source;
    cout << "\nEnter source vertex: ";
    cin >> source;

    graph.dijkstra(source);

    return 0;
}