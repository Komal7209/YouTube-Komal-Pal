/*
Steps:

1. Initialize distances
    dist[source] = 0
    All other distances = ∞

2. Use a Min-Heap (Priority Queue)
    Store pairs: {distance, node}

3. Pick the nearest unvisited node
    u = min distance from heap

4. Relax its neighbors
    For each neighbor v of u:

    if dist[u] + weight(u, v) < dist[v]:
        dist[v] = dist[u] + weight(u, v)
        push (dist[v], v) into heap

5. Mark u as visited
6. Repeat steps 3–5 until heap is empty

*/

#include <bits/stdc++.h>
using namespace std;

vector<int> dijkstra(int V, vector<vector<pair<int,int>>> &adj, int S)
{
    // Min-heap: (distance, node)
    priority_queue<pair<int,int>,
                   vector<pair<int,int>>,
                   greater<pair<int,int>>> pq;

    vector<int> dist(V, INT_MAX);

    dist[S] = 0;
    pq.push({0, S});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (auto &edge : adj[u]) {
            int v = edge.first;
            int wt = edge.second;

            if (dist[u] + wt < dist[v]) {
                dist[v] = dist[u] + wt;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

/*

graph:

0 --1--> 1
0 --4--> 2
1 --2--> 2
1 --5--> 3
2 --1--> 3

adjacency list:

adj[0] = {{1,1},{2,4}};
adj[1] = {{2,2},{3,5}};
adj[2] = {{3,1}};

call:
vector<int> result = dijkstra(4, adj, 0);


output:
0 → 0 = 0
0 → 1 = 1
0 → 2 = 3
0 → 3 = 4

*/

/*

| Part                   | Complexity     |
| ---------------------- | -------------- |
| Each node in heap      | log V          |
| Each edge relaxed once | E              |
| Total Time             | O(E log V)     |
| Space                  | O(V + E)       |


*/

/*

Dijkstra = “How do I reach?”
Prim = “What should I connect next?”

*/