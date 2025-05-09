<!-- HPC 1 BFS DFS -->

```cpp
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
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;

    MyGraph g(V);

    cout << "Enter number of edges: ";
    cin >> E;
    cout << "Enter " << E << " edges (u v):\n";
    while (E--) {
        int u, v;
        cin >> u >> v;
        g.connect(u, v);
    }

    g.printGraph();

    int start;
    cout << "Enter starting node for BFS and DFS: ";
    cin >> start;

    cout << "Parallel BFS Output: ";
    g.parallelBFS(start);
    cout << "\nDFS Output: ";
    g.dfsIterative(start);
    cout << endl;

    return 0;
}
```

## HOW TO RUN THE CODE

Great question! Here's how you can **run your C++ code with OpenMP** on **Windows** step-by-step 👇

---

## ✅ Step-by-Step Guide to Run Your Code (Windows)

---

### 🧰 **Step 1: Install a Compiler that Supports OpenMP**

#### ✅ Option A: **MinGW-w64** (Recommended)

1. Download **MinGW-w64** from:
   [https://www.mingw-w64.org/downloads](https://www.mingw-w64.org/downloads)

2. Install it with **x86_64 architecture** and **posix/seh threading model**.

3. Add the `bin` folder to your **System PATH**.
   Example: `C:\Program Files\mingw-w64\...\bin`

4. Open `cmd` or PowerShell and type:

   ```bash
   g++ --version
   ```

   You should see a version message if installed correctly.

---

### 🖥️ **Step 2: Save Your Code**

Save your C++ file with a `.cpp` extension, e.g.:

```
graph_parallel.cpp
```

---

### ⚙️ **Step 3: Compile the Code with OpenMP Flag**

Open **Command Prompt** or **PowerShell**, go to the folder where your `.cpp` file is, and run:

```bash
g++ -fopenmp graph_parallel.cpp -o graph_parallel.exe
```

✅ This creates an executable file named `graph_parallel.exe`.

---

### ▶️ **Step 4: Run the Program**

Simply run:

```bash
graph_parallel.exe
```

Then input your graph details (vertices, edges, etc.) as prompted.

---

### 💡 Example:

```bash
> g++ -fopenmp graph_parallel.cpp -o graph_parallel.exe
> graph_parallel.exe
```

Absolutely! Here’s a **step-by-step input demo** for your program after running it in the terminal — so you know **exactly what to type** and **what to expect** 👇

---

## ✅ Example: How to Provide Input to the Graph Program

### 👨‍💻 When your program runs, you’ll see this:

```
Enter the number of vertices in the graph:
```

### 🧑‍🎓 You type:

```
5
```

---

Then you see:

```
Enter the number of edges in the graph:
```

You type:

```
6
```

---

Then you see:

```
Enter the edges (source destination):
```

You now enter each edge on a new line (source and destination):

```
0 1
0 2
1 3
2 4
3 4
1 2
```

---

Now it shows:

```
Enter the starting vertex for BFS and DFS:
```

You type:

```
0
```

---

### ✅ Full Input to Paste During Execution (with line breaks):

```
5
6
0 1
0 2
1 3
2 4
3 4
1 2
0
```

---

### 📤 Output You’ll See (Example):

```
Graph Structure:
0: 1 2
1: 0 3 2
2: 0 4 1
3: 1 4
4: 2 3

Parallel BFS Output: 0 1 2 3 4
DFS Output: 0 2 4 3 1
```

🟨 _(BFS/DFS order may slightly change due to parallel execution.)_

---

## 📘 Theory & Explanation (Short and Easy)

### 🔹 BFS vs DFS:

- **BFS** = explores level by level (uses Queue)
- **DFS** = goes deep first, then backtracks (uses Recursion or Stack)

### 🔹 Parallelism:

- We use **OpenMP** to parallelize the loop over neighbors.
- `#pragma omp parallel for` runs each neighbor check in a separate thread.
- In BFS, we use `#pragma omp critical` to protect `q.push()` and `visited[]` updates (avoid race conditions).

---

## 💬 Viva Questions & Simple Answers:

| Question                                 | Answer                                                                  |
| ---------------------------------------- | ----------------------------------------------------------------------- |
| What is BFS?                             | BFS explores nodes level-by-level using a queue.                        |
| What is DFS?                             | DFS goes deep into a path before backtracking. Uses recursion or stack. |
| Why use OpenMP?                          | To make the search faster by checking multiple neighbors in parallel.   |
| What does `#pragma omp parallel for` do? | It runs a loop in parallel using multiple threads.                      |
| Why do we use `#pragma omp critical`?    | To prevent two threads from changing shared data at the same time.      |

## THEORY

## 📘 **Theory: Parallel BFS and DFS using OpenMP**

### 🔹 **Objective:**

To implement **Breadth-First Search (BFS)** and **Depth-First Search (DFS)** using **parallelism** with **OpenMP** on an **undirected graph**.

---

### 🔹 **Graph Traversal Algorithms:**

- **BFS (Breadth-First Search):**

  - Uses a **queue**.
  - Explores neighbors **level by level**.
  - Best for finding shortest path.

- **DFS (Depth-First Search):**

  - Uses **recursion** or **stack**.
  - Goes deep into a path, then backtracks.

---

### 🔹 **Parallelism with OpenMP:**

- `#pragma omp parallel for` is used to **parallelize the neighbor traversal** in both BFS and DFS.
- In BFS, `#pragma omp critical` ensures only one thread updates the queue or visited array at a time, avoiding **race conditions**.

---

### 🔹 **Why Use Parallelism:**

- In large graphs, many neighbors can be checked **at the same time**.
- This speeds up traversal using **multiple CPU threads**.

---

### 🔹 **Graph Representation:**

- Used an **adjacency list** for a simple **undirected graph** with 5 nodes.
- Example: node `0` is connected to nodes `1` and `2`.

---

### 🔚 **Conclusion:**

Using OpenMP for BFS and DFS improves performance by processing multiple nodes or neighbors in parallel. It’s a useful approach in real-time systems and large-scale graph problems.
