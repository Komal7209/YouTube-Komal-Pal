// used for dense graph

/*
Steps:

1. Create three arrays:
    key[] → minimum edge weight to connect node to MST
    mst[] → whether node is included in MST
    parent[] → stores MST

2. Initialize:
    key[0] = 0        (start from 0)
    parent[0] = -1
    All other keys = ∞


3. Repeat V times:

    Pick the unvisited node with minimum key value
    Mark it as visited (MST)
    Update its neighbors:

    If graph[u][v] < key[v] and v not in MST
        key[v] = graph[u][v]
        parent[v] = u


4. At the end:
    Parent array represents MST
    Sum of keys = MST cost

*/

#include <bits/stdc++.h>
using namespace std;


int primsMST(vector<vector<int>>& graph) {
    int V = graph.size();
    
    vector<int> key(V, INT_MAX);     // minimum weight to connect
    vector<bool> inMST(V, false);    // visited
    vector<int> parent(V, -1);       
    
    key[0] = 0;   // start from node 0
    
    for (int count = 0; count < V - 1; count++) {

        int u = -1;
        int mini = INT_MAX;

        // Pick minimum key node not in MST
        for (int i = 0; i < V; i++) {
            if (!inMST[i] && key[i] < mini) {
                mini = key[i];
                u = i;
            }
        }

        inMST[u] = true;

        // Update adjacent vertices of u
        for (int v = 0; v < V; v++) {
            if (graph[u][v] != 0 &&
                !inMST[v] &&
                graph[u][v] < key[v]) {

                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    // Total cost of MST
    int cost = 0;
    for (int i = 1; i < V; i++) {
        cost += graph[i][parent[i]];
    }

    return cost;
}


/*
🅑 Prim’s using Adjacency Matrix (Basic version)

No heap, just array scanning.
Here V is number of nodes

⏱ Time Complexity: O(V^2)
	
This is used for dense graphs.

💾 Space Complexity: O(V^2)

*/

/*
example walkthrough:

graph:

    0  1  2  3
0 [ 0, 2, 0, 6 ]
1 [ 2, 0, 3, 8 ]
2 [ 0, 3, 0, 0 ]
3 [ 6, 8, 0, 0 ]

call:

vector<vector<int>> graph = {
    {0, 2, 0, 6},
    {2, 0, 3, 8},
    {0, 3, 0, 0},
    {6, 8, 0, 0}
};

cout << primsMST(graph);

Output will be: 11


*/