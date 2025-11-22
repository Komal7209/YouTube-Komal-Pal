/*
Steps:

1. We relax every edge n – 1 times
2. Each time, we try to update:
    dist[v] = min(dist[v], dist[u] + weight)
3. After n-1 relaxations, if anything still changes → negative cycle exists

*/

#include <bits/stdc++.h>
using namespace std;

vector<int> bellmanFord(int n, vector<vector<int>>& edges, int src) {

    vector<int> dist(n, 1e9);   // start with infinity
    dist[src] = 0;

    // Relax all edges (n-1) times
    for (int i = 0; i < n - 1; i++) {
        for (auto &e : edges) {
            int u = e[0];
            int v = e[1];
            int w = e[2];

            if (dist[u] != 1e9 && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    // Optional: detect negative cycle
    for (auto &e : edges) {
        int u = e[0];
        int v = e[1];
        int w = e[2];

        if (dist[u] != 1e9 && dist[u] + w < dist[v]) {
            cout << "Negative Cycle Detected\n";
            return {};
        }
    }

    return dist;
}


/*
| Metric | Value        |
| ------ | ------------ |
| Time   | O(V × E)     |
| Space  | O(V)         |

*/


/*
✅ Negative weights
✅ Detect negative cycles
❌ Slower than Dijkstra
*/