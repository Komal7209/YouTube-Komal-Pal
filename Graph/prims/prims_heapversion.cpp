/*
Steps:

1. Start with any node (here: 0)
2. Always take the cheapest edge that connects:
    A node in MST → A node not in MST
3. Repeat until all nodes are included
*/

class Solution {
public:
    int prims(int n, vector<vector<int>>& edges) {

        // Step 1: Build Adjacency List
        vector<vector<pair<int,int>>> adj(n);

        for (auto &e : edges) {
            int u = e[0], v = e[1], w = e[2];
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }

        // Step 2: Min-Heap {weight, node}
        priority_queue<pair<int,int>,
                       vector<pair<int,int>>,
                       greater<pair<int,int>>> pq;

        vector<bool> inMST(n, false);

        // Start from node 0
        pq.push({0, 0});   // {weight, node}

        int mstWeight = 0;

        // Step 3: Process nodes
        while (!pq.empty()) {
            auto [weight, node] = pq.top();
            pq.pop();

            if (inMST[node]) continue;

            inMST[node] = true;
            mstWeight += weight;

            for (auto &nbr : adj[node]) {
                int next = nbr.first;
                int cost = nbr.second;

                if (!inMST[next]) {
                    pq.push({cost, next});
                }
            }
        }

        return mstWeight;
    }
};

/*
🅐 Prim’s using Min-Heap (Priority Queue) (Most used in interviews) used for All graphs

Data structure used:
Min-heap + Adjacency list

⏱ Time Complexity

Remove/insert from heap for each edge: O(ElogV)
	​

💾 Space Complexity

We store:

Adjacency list → O(E)

Heap → O(V)

Visited array → O(V)

O(E+V)

*/

/*
0 -1- 1
|     |
4     2
|     |
3 -3- 2


Start at 0:

pick edge 0-1 (1) ✅

then 1-2 (2) ✅

then 2-3 (3) ✅

MST = 1 + 2 + 3 = 6

*/

/*

| Prim’s                    | Kruskal                       |
| ------------------------- | ----------------------------- |
| Grows one tree        | Grows multiple components     |
| Uses Min-Heap         | Uses  Sorting + DSU.          |
| Good for dense graphs | Good for sparse graphs        |
| Starts from one node  | No start needed               |


*/