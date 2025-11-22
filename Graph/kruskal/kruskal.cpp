/*

Steps:

1. Sort all edges in increasing order of weight.
2. Pick the smallest edge first.
3. Add it only if it does NOT create a cycle.
4. Use DSU (Union-Find) to quickly check cycle.
5. Stop after using n − 1 edges.

*/

class DSU {
public:
    vector<int> parent, rankv;

    DSU(int n) {
        parent.resize(n);
        rankv.resize(n, 0);
        for(int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x) {
        if(parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int x, int y) {
        int px = find(x);
        int py = find(y);

        if (px == py) return false;

        if (rankv[px] < rankv[py])
            parent[px] = py;
        else if (rankv[px] > rankv[py])
            parent[py] = px;
        else {
            parent[py] = px;
            rankv[px]++;
        }

        return true;
    }
};

class Solution {
public:
    int kruskal(int n, vector<vector<int>>& edges) {

        // Sort edges by weight
        sort(edges.begin(), edges.end(),
            [](vector<int>& a, vector<int>& b){
                return a[2] < b[2];
            });

        DSU dsu(n);
        int mstWeight = 0;
        int count = 0;

        for (auto &e : edges) {
            int u = e[0], v = e[1], w = e[2];

            if (dsu.unite(u, v)) {   // if no cycle is formed
                mstWeight += w;
                count++;

                if (count == n - 1)
                    break;
            }
        }

        return mstWeight;
    }
};

/*
Let:

V = number of vertices

E = number of edges

⏱ Time Complexity

Main steps in Kruskal:

Sort all edges: O(E log E)
DSU operations (union/find) for each edge: O(E α(V)) ≈ O(E)   (α is inverse Ackermann – almost constant)

✅ Final Time Complexity: O(ElogE)
	
Since E ≈ V², sometimes written as:  O(ElogV)


💾 Space Complexity

We store:

Edge list → O(E)

Parent & Rank arrays (DSU) → O(V)

O(E+V)
*/

/*
edges:

(0-1,1), (1-2,2), (0-2,3)


sorted:
(0-1,1) ✅
(1-2,2) ✅
(0-2,3) ❌ (cycle)

MST: 1 + 2 = 3

*/