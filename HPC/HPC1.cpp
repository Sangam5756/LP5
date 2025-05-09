#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <omp.h>

using namespace std;

class MyGraph {
    int V;
    vector<vector<int>> edges;

public:
    MyGraph(int vertices) {
        V = vertices;
        edges.resize(V);
    }

    void connect(int u, int v) {
        edges[u].push_back(v);
        edges[v].push_back(u); // undirected
    }

    void printGraph() {
        cout << "Graph Structure:\n";
        for (int i = 0; i < V; i++) {
            cout << i << ": ";
            for (int j : edges[i])
                cout << j << " ";
            cout << endl;
        }
    }

    // BFS with OpenMP (Parallel neighbor processing)
    void parallelBFS(int source) {
        vector<bool> visited(V, false);
        queue<int> current;
        current.push(source);
        visited[source] = true;

        while (!current.empty()) {
            int n = current.size();
            vector<int> next;

            #pragma omp parallel for
            for (int i = 0; i < n; i++) {
                int node;

                #pragma omp critical
                {
                    if (!current.empty()) {
                        node = current.front();
                        current.pop();
                        cout << node << " ";
                    }
                }

                for (int neighbor : edges[node]) {
                    #pragma omp critical
                    {
                        if (!visited[neighbor]) {
                            visited[neighbor] = true;
                            next.push_back(neighbor);
                        }
                    }
                }
            }

            for (int v : next)
                current.push(v);
        }
    }

    // Iterative DFS
    void dfsIterative(int start) {
        vector<bool> visited(V, false);
        stack<int> stk;
        stk.push(start);
        visited[start] = true;

        while (!stk.empty()) {
            int node = stk.top();
            stk.pop();
            cout << node << " ";

            for (int neighbor : edges[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    stk.push(neighbor);
                }
            }
        }
    }
};
int main() {
    int V = 5;
    MyGraph g(V);

    // Hardcoded edges (same as before)
    g.connect(0, 1);
    g.connect(0, 2);
    g.connect(1, 3);
    g.connect(2, 4);
    g.connect(3, 4);
    g.connect(1, 2);

    g.printGraph();

    int start = 0; // fixed start node
    cout << "Parallel BFS Output: ";
    g.parallelBFS(start);
    cout << "\nDFS Output: ";
    g.dfsIterative(start);
    cout << endl;

    return 0;
}
